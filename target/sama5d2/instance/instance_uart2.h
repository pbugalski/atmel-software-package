/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2015, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */

#ifndef _SAMA5D2_UART2_INSTANCE_
#define _SAMA5D2_UART2_INSTANCE_

/* ========== Register definition for UART2 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_UART2_CR                       (0xF8024000U) /**< \brief (UART2) Control Register */
  #define REG_UART2_MR                       (0xF8024004U) /**< \brief (UART2) Mode Register */
  #define REG_UART2_IER                      (0xF8024008U) /**< \brief (UART2) Interrupt Enable Register */
  #define REG_UART2_IDR                      (0xF802400CU) /**< \brief (UART2) Interrupt Disable Register */
  #define REG_UART2_IMR                      (0xF8024010U) /**< \brief (UART2) Interrupt Mask Register */
  #define REG_UART2_SR                       (0xF8024014U) /**< \brief (UART2) Status Register */
  #define REG_UART2_RHR                      (0xF8024018U) /**< \brief (UART2) Receive Holding Register */
  #define REG_UART2_THR                      (0xF802401CU) /**< \brief (UART2) Transmit Holding Register */
  #define REG_UART2_BRGR                     (0xF8024020U) /**< \brief (UART2) Baud Rate Generator Register */
  #define REG_UART2_CMPR                     (0xF8024024U) /**< \brief (UART2) Comparison Register */
  #define REG_UART2_RTOR                     (0xF8024028U) /**< \brief (UART2) Receiver Time-out Register */
  #define REG_UART2_WPMR                     (0xF80240E4U) /**< \brief (UART2) Write Protection Mode Register */
  #define REG_UART2_VERSION                  (0xF80240FCU) /**< \brief (UART2) Version Register */
#else
  #define REG_UART2_CR      (*(__O  uint32_t*)0xF8024000U) /**< \brief (UART2) Control Register */
  #define REG_UART2_MR      (*(__IO uint32_t*)0xF8024004U) /**< \brief (UART2) Mode Register */
  #define REG_UART2_IER     (*(__O  uint32_t*)0xF8024008U) /**< \brief (UART2) Interrupt Enable Register */
  #define REG_UART2_IDR     (*(__O  uint32_t*)0xF802400CU) /**< \brief (UART2) Interrupt Disable Register */
  #define REG_UART2_IMR     (*(__I  uint32_t*)0xF8024010U) /**< \brief (UART2) Interrupt Mask Register */
  #define REG_UART2_SR      (*(__I  uint32_t*)0xF8024014U) /**< \brief (UART2) Status Register */
  #define REG_UART2_RHR     (*(__I  uint32_t*)0xF8024018U) /**< \brief (UART2) Receive Holding Register */
  #define REG_UART2_THR     (*(__O  uint32_t*)0xF802401CU) /**< \brief (UART2) Transmit Holding Register */
  #define REG_UART2_BRGR    (*(__IO uint32_t*)0xF8024020U) /**< \brief (UART2) Baud Rate Generator Register */
  #define REG_UART2_CMPR    (*(__IO uint32_t*)0xF8024024U) /**< \brief (UART2) Comparison Register */
  #define REG_UART2_RTOR    (*(__IO uint32_t*)0xF8024028U) /**< \brief (UART2) Receiver Time-out Register */
  #define REG_UART2_WPMR    (*(__IO uint32_t*)0xF80240E4U) /**< \brief (UART2) Write Protection Mode Register */
  #define REG_UART2_VERSION (*(__I  uint32_t*)0xF80240FCU) /**< \brief (UART2) Version Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_UART2_INSTANCE_ */