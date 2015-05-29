/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

#include <stdint.h>

#include "board.h"
#include "chip.h"

#include "core/wdt.h"
#include "core/pmc.h"
#include "core/aic.h"
#include "core/pio.h"

#include "bus/console.h"

#include "mem/at25df321.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_BUFFER_SIZE  128
#define READ_BUFFER_SIZE  128

static uint8_t cmd_buffer[CMD_BUFFER_SIZE];
static uint8_t read_buffer[READ_BUFFER_SIZE];

typedef void (*_parser)(const uint8_t*, uint32_t);

static _parser _cmd_parser;

static void console_handler(void)
{
	volatile static uint32_t lock = 0;
	static uint32_t index = 0;
	uint8_t key;
	if (!console_is_rx_ready())
		return;
	key = console_get_char();
	if (lock)
		return;
	lock = 1;
	if (index >= CMD_BUFFER_SIZE) {
		printf("\r\nWARNING! command buffer size exeeded, "
		       "reseting\r\n");
		index = 0;
	}
	console_echo(key);
	switch (key) {
	case '\r':
	case '\n':
		cmd_buffer[index]='\0';
		_cmd_parser(cmd_buffer, index);
		index = 0;
		break;
	case 0x7F:
	case '\b':
		cmd_buffer[--index]='\0';
		break;
	default:
		cmd_buffer[index++]=key;
		break;
	}
	lock = 0;
}

static void _flash_read_arg_parser(const uint8_t* buffer, uint32_t len)
{
	char* end_addr = NULL;
	char* end_length = NULL;
	unsigned long addr = strtoul((char*)buffer, &end_addr, 0);
	if (end_addr == (char*)buffer) {
		printf("Args: %s"
		       "Invalid address\r\n",
		       buffer);
		return;
	}

	int length = strtol(end_addr, &end_length, 0);
	if (end_length == end_addr) {
		printf("Args: %s"
		       "Invalid size\r\n",
			buffer);
		return;
	}
	int offset = 0;
	while (length > READ_BUFFER_SIZE) {
		at25df321_read_stream(addr+offset, read_buffer,
				      READ_BUFFER_SIZE);
		offset += READ_BUFFER_SIZE;
		length -= READ_BUFFER_SIZE;
		console_dump_frame(read_buffer, READ_BUFFER_SIZE);

	}
	at25df321_read_stream(addr+offset, read_buffer,
			length);
	console_dump_frame(read_buffer, length);
}

static void _flash_write_arg_parser(const uint8_t* buffer, uint32_t len)
{
	char* end_addr = NULL;
	unsigned int addr = strtoul((char*)buffer, &end_addr, 0);
	if (end_addr == (char*)buffer) {
		printf("Args: %s"
		       "Invalid address\r\n",
			buffer);
		return;
	}

	at25df321_write_stream(addr, (uint8_t*)end_addr, len);
}

static void _flash_query_arg_parser(const uint8_t* buffer, uint32_t len)
{
	const char *dev_lbl = "device";
	const char *status_lbl = "status";
	if (!strncmp((char*)buffer, dev_lbl, 6)) {
		at25df321_print_device_info();
	} else if (!strncmp((char*)buffer, status_lbl, 6)) {
		at25df321_get_status();
	}
}

static void _flash_cmd_parser(const uint8_t* buffer, uint32_t len)
{

	if (*(buffer+1) != ' ') {
		printf("Commands can only be one caracter size\r\n");
		printf("%c%c\r\n", *buffer, *(buffer+1));
		return;
	}
	switch(*buffer) {
	case 'r':
		_flash_read_arg_parser(buffer+2, len-2);
		break;
	case 'w':
		_flash_write_arg_parser(buffer+2, len-2);
		break;
	case 'a':
		_flash_query_arg_parser(buffer+2, len-2);
		break;
	default:
		printf("Command %c unknown\r\n", *buffer);
	}

}

int main (void)
{
	/* Disable watchdog */
	WDT_Disable(WDT);

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	/* Initialize console */
	console_configure(CONSOLE_BAUDRATE);

	/* Configure console interrupts */
	console_enable_interrupts(US_IER_RXRDY);
	aic_set_source_vector(CONSOLE_ID, console_handler);
	aic_enable(CONSOLE_ID);
	_cmd_parser = _flash_cmd_parser;

#if defined (ddram)
	mmu_initialize((uint32_t *) 0x20C000);
	cp15_enable_mmu();
	cp15_enable_dcache();
	cp15_enable_icache();
#endif

	/* Clear console */
	console_clear_screen();
	console_reset_cursor();

	printf("-- Spi flash Example " SOFTPACK_VERSION " --\n\r"
	       "-- " BOARD_NAME " --\n\r"
	       "-- Compiled: " __DATE__ " at " __TIME__ " --\n\r");

	/* Open serial flash device */
	at25df321_open();
	/* at25df321_unlock_sectors(); */

	while (1);
}