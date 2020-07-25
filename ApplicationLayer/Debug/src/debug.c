/*
 * debug.c
 *
 *  Created on: 31 мая 2020 г.
 *      Author: 1311985
 */
#include "debug.h"
#include "callbacks.h"

int16_t ai16TxBuffer[TX_BUFFER_SIZE];
uint8_t au8RxBuffer[RX_BUFFER_SIZE];
SensorProcessing_SensorValues_t *ptSensorValues;

static void USART_Init(void);
static void DMA_Init(void);
static void BufferTransmit(uint8_t u8BufferLength);

void Debug_Init(void)
{
	USART_Init();
	DMA_Init();
}

void Debug_Routine_2ms(void)
{
	//(void)SensorProcessing_ApiGetSensorValues(&ai16TxBuffer[0], 0);
	(void)SensorProcessing_ApiGetSensorValues(&ptSensorValues, 0);
	ai16TxBuffer[0] = ptSensorValues->i16FilteredValue;
	ai16TxBuffer[1] = ptSensorValues->i16DerivativeValue * 10;
	//ai16TxBuffer[2] = (int16_t)(ptSensorValues->tState) * 1000;
	ai16TxBuffer[2] = ptSensorValues->i16DeltaValue;
	BufferTransmit(6);
}

static void USART_Init(void)
{

	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);

	USART_CLK_ENABLE();

	/* Configure Tx Pin as : Alternate function, High Speed, Push pull, Pull up */
	LL_GPIO_SetPinMode(USART_TX_GPIO_PORT, USART_TX_PIN, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(USART_TX_GPIO_PORT, USART_TX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(USART_TX_GPIO_PORT, USART_TX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(USART_TX_GPIO_PORT, USART_TX_PIN, LL_GPIO_PULL_UP);

	/* Configure Rx Pin as : Input Floating function, High Speed, Pull up */
	LL_GPIO_SetPinMode(USART_RX_GPIO_PORT, USART_RX_PIN, LL_GPIO_MODE_FLOATING);
	LL_GPIO_SetPinSpeed(USART_RX_GPIO_PORT, USART_RX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinPull(USART_RX_GPIO_PORT, USART_RX_PIN, LL_GPIO_PULL_UP);


	/* Configure USART functional parameters ********************************/

	/* TX/RX direction */
	LL_USART_SetTransferDirection(USART_DEBUG_INSTANCE, LL_USART_DIRECTION_TX_RX);

	/* 8 data bit, 1 start bit, 1 stop bit, no parity */
	LL_USART_ConfigCharacter(USART_DEBUG_INSTANCE, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);


	/* Set Baudrate to 115200 using APB frequency set to 8000000/APB_Div Hz */
	LL_USART_SetBaudRate(USART_DEBUG_INSTANCE, SystemCoreClock, 115200);

	LL_USART_EnableDMAReq_TX(USART_DEBUG_INSTANCE);

	LL_USART_Enable(USART_DEBUG_INSTANCE);
}

static void DMA_Init(void)
{
	NVIC_SetPriority(DMA_RX_CHANNEL_IRQn, NVIC_DEBUG_DMA_RX_PRIORITY);
	NVIC_EnableIRQ(DMA_RX_CHANNEL_IRQn);
	NVIC_SetPriority(DMA_TX_CHANNEL_IRQn, NVIC_DEBUG_DMA_TX_PRIORITY);
	NVIC_EnableIRQ(DMA_TX_CHANNEL_IRQn);

	LL_DMA_ConfigTransfer(DMA1, DMA_TX_CHANNEL,
	                      LL_DMA_DIRECTION_MEMORY_TO_PERIPH |
	                      LL_DMA_PRIORITY_LOW               |
	                      LL_DMA_MODE_CIRCULAR              |
	                      LL_DMA_PERIPH_NOINCREMENT         |
	                      LL_DMA_MEMORY_INCREMENT           |
	                      LL_DMA_PDATAALIGN_BYTE            |
	                      LL_DMA_MDATAALIGN_BYTE);
	LL_DMA_ConfigAddresses(DMA1, DMA_TX_CHANNEL,
	                       (uint32_t)ai16TxBuffer,
	                       LL_USART_DMA_GetRegAddr(USART_DEBUG_INSTANCE),
	                       LL_DMA_GetDataTransferDirection(DMA1, DMA_TX_CHANNEL));
	//DMA_SET_DATALENGTH_TRANSMIT(SENSORS_AMOUNT * 2);
	//LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_7, ubNbDataToTransmit);


	LL_DMA_ConfigTransfer(DMA1, DMA_RX_CHANNEL,
	                      LL_DMA_DIRECTION_PERIPH_TO_MEMORY |
	                      LL_DMA_PRIORITY_LOW               |
	                      LL_DMA_MODE_NORMAL                |
	                      LL_DMA_PERIPH_NOINCREMENT         |
	                      LL_DMA_MEMORY_INCREMENT           |
	                      LL_DMA_PDATAALIGN_BYTE            |
	                      LL_DMA_MDATAALIGN_BYTE);
	LL_DMA_ConfigAddresses(DMA1, DMA_RX_CHANNEL,
	                       LL_USART_DMA_GetRegAddr(USART_DEBUG_INSTANCE),
	                       (uint32_t)au8RxBuffer,
	                       LL_DMA_GetDataTransferDirection(DMA1, DMA_RX_CHANNEL));
	DMA_SET_DATALENGTH_RECEIVE(DMA_DEFAULT_DATALENGTH_RECEIVE);

	LL_DMA_EnableIT_TC(DMA1, DMA_RX_CHANNEL);
	LL_DMA_EnableIT_TC(DMA1, DMA_TX_CHANNEL);
}

static void BufferTransmit(uint8_t u8BufferLength)
{
	DMA_SET_DATALENGTH_TRANSMIT(u8BufferLength);

	LL_DMA_EnableChannel(DMA1, DMA_TX_CHANNEL);
}

void DMA_UsartTransmitComplete_Callback(void)
{
	LL_DMA_DisableChannel(DMA1, DMA_TX_CHANNEL);
}

void DMA_UsartReceiveComplete_Callback(void)
{
	LL_DMA_DisableChannel(DMA1, DMA_RX_CHANNEL);
}
