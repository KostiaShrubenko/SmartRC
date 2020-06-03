/*
 * debug.h
 *
 *  Created on: 31 мая 2020 г.
 *      Author: 1311985
 */

#ifndef DEBUG_INC_DEBUG_H_
#define DEBUG_INC_DEBUG_H_

#include "main.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_dma.h"
#include "CapSens_Api.h"
#include "SensorProcessing_Api.h"
#include "string.h"

#define USART_DEBUG_INSTANCE         USART1
#define USART_CLK_ENABLE()           LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)

#define USART_TX_PIN                 LL_GPIO_PIN_9
#define USART_TX_GPIO_PORT           GPIOA
#define USART_SET_TX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_9, LL_GPIO_AF_7)
#define USART_RX_PIN                 LL_GPIO_PIN_10
#define USART_RX_GPIO_PORT           GPIOA
#define USART_SET_RX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_10, LL_GPIO_AF_7)



#define DMA_RX_CHANNEL		LL_DMA_CHANNEL_5
#define DMA_TX_CHANNEL		LL_DMA_CHANNEL_4

#define DMA_RX_CHANNEL_IRQn	DMA1_Channel5_IRQn
#define DMA_TX_CHANNEL_IRQn DMA1_Channel4_IRQn

#define DMA_SET_DATALENGTH_TRANSMIT(length) LL_DMA_SetDataLength(DMA1, DMA_TX_CHANNEL, (length))
#define DMA_SET_DATALENGTH_RECEIVE(length) 	LL_DMA_SetDataLength(DMA1, DMA_RX_CHANNEL, (length))

#define DMA_DEFAULT_DATALENGTH_RECEIVE 1U

#define TX_BUFFER_SIZE 20U
#define RX_BUFFER_SIZE 20U

void Debug_Init(void);

void Debug_Routine_2ms(void);

#endif /* DEBUG_INC_DEBUG_H_ */
