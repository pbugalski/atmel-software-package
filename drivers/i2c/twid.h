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

#ifndef TWID_H_
#define TWID_H_

/*------------------------------------------------------------------------------
 *        Header
 *----------------------------------------------------------------------------*/

#include "i2c/twi.h"
#include "dma/dma.h"
#include "mutex.h"
#include "io.h"

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

#define TWID_SUCCESS         (0)
#define TWID_INVALID_ID      (1)
#define TWID_INVALID_BITRATE (2)
#define TWID_ERROR_LOCK      (3)
#define TWID_ERROR_DUPLEX    (4)
#define TWID_ERROR_ACK       (5)
#define TWID_ERROR_TIMEOUT   (6)
#define TWID_ERROR_TRANSFER  (7)

#define TWID_TRANSFER_IN_PROGRESS  (0x80)

enum _twid_buf_attr {
	TWID_BUF_ATTR_START  = 0x01,
	TWID_BUF_ATTR_STOP   = 0x02,
	TWID_BUF_ATTR_READ   = 0x04,
	TWID_BUF_ATTR_WRITE  = 0x08,
};

enum _twid_trans_mode
{
	TWID_MODE_POLLING,
	TWID_MODE_DMA,
	TWID_MODE_ASYNC,
};

struct _twi_desc;

typedef void (*twid_callback_t)(struct _twi_desc* twi, void* args);

struct _twi_desc
{
	Twi*  addr;
	uint32_t freq;
	uint32_t slave_addr;
	enum _twid_trans_mode transfer_mode;
	uint32_t flags;
	uint32_t timeout; /**< timeout (if 0, a default timeout is used) */
	/* implicit internal padding is mandatory here */
	mutex_t mutex;
	twid_callback_t callback;
	void*   cb_args;

#ifdef CONFIG_HAVE_TWI_FIFO
	bool use_fifo;
	struct {
		struct {
			uint16_t size;
			uint16_t threshold;
		} rx, tx;
	} fifo;
#endif

	struct {
		struct {
			struct dma_channel *channel;
			struct dma_xfer_cfg cfg;
		} rx;
		struct {
			struct dma_channel *channel;
			struct dma_xfer_cfg cfg;
		} tx;
	} dma;
};

struct _twi_slave_ops {
	void (*on_start)(void);
	void (*on_stop)(void);
	int16_t (*on_read)(uint8_t byte);
	int16_t (*on_write)(void);
};

struct _twi_slave_desc {
	Twi* twi;
	uint16_t addr;
	uint8_t state;
#define TWID_SLAVE_STATE_STOPPED 0
#define TWID_SLAVE_STATE_STARTED 1
	struct _twi_slave_ops* ops;
};

/*------------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

extern void twid_configure(struct _twi_desc* desc);

extern void twid_slave_configure(struct _twi_slave_desc* desc, struct _twi_slave_ops* ops);

extern uint32_t twid_transfer(struct _twi_desc* desc, struct _buffer* buf, int buffers,
                              twid_callback_t cb, void* user_args);

extern uint32_t twid_is_busy(const struct _twi_desc* desc);

extern void twid_wait_transfer(const struct _twi_desc* desc);

#endif /* TWID_H_ */
