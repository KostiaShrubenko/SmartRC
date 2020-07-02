/*
 * CapSens.c
 *
 *  Created on: 15 мая 2020 г.
 *      Author: 1311985
 */

#include "CapSens.h"
#include "callbacks.h"

static LL_GPIO_InitTypeDef tConfigTopConnection;
static LL_GPIO_InitTypeDef tConfigBottomConnection;

__IO uint16_t 	au16SensorsValue[SENSORS_AMOUNT];
__IO uint8_t	u8DMA_ADCtransferStatus = DMA_NO_TRANSFER;


static void DMA_Init(void);
static void ADC_Init(void);
static void ADC_Activate(void);

void CapSens_InitRoutine(void)
{
	TOP_CLK_ENABLE();
	BOTTOM_CLK_ENABLE();

	tConfigBottomConnection.Pin = BOTTOM_PINS;
	tConfigBottomConnection.Mode = LL_GPIO_MODE_OUTPUT;
	tConfigBottomConnection.Speed = LL_GPIO_SPEED_FREQ_LOW;
	tConfigBottomConnection.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	tConfigBottomConnection.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(BOTTOM_PORT, &tConfigBottomConnection);

	tConfigTopConnection.Pin = TOP_PINS;
	tConfigTopConnection.Mode = LL_GPIO_MODE_OUTPUT;
	tConfigTopConnection.Speed = LL_GPIO_SPEED_FREQ_LOW;
	tConfigTopConnection.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	tConfigTopConnection.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(TOP_PORT, &tConfigTopConnection);

	DMA_Init();
	ADC_Init();
	ADC_Activate();
}

void CapSens_ChargeRoutine_2ms(void)
{
	for (uint16_t i = 0; i < CHARGE_CYCLES; i++)
	{
		MODIFY_REG(BOTTOM_PORT->CRL, BOTTOM_CRL_MASK, BOTTOM_CRL_MODE_FLOAT);
		MODIFY_REG(BOTTOM_PORT->CRH, BOTTOM_CRH_MASK, BOTTOM_CRH_MODE_FLOAT);

		MODIFY_REG(TOP_PORT->CRL, TOP_CRL_MASK, TOP_MODE_OUTPUT);
		MODIFY_REG(TOP_PORT->ODR, TOP_PINS_MASK, TOP_HIGH_LEVEL); /* Set High Level to Top pins */


		MODIFY_REG(TOP_PORT->CRL, TOP_CRL_MASK, TOP_MODE_FLOAT);

		MODIFY_REG(BOTTOM_PORT->CRL, BOTTOM_CRL_MASK, BOTTOM_CRL_MODE_OUTPUT);
		MODIFY_REG(BOTTOM_PORT->CRH, BOTTOM_CRH_MASK, BOTTOM_CRH_MODE_OUTPUT);
		MODIFY_REG(BOTTOM_PORT->ODR, BOTTOM_PINS_MASK, BOTTOM_LOW_LEVEL); /* Set Low Level to Bottom pins */
	}
	MODIFY_REG(TOP_PORT->CRL, TOP_CRL_MASK, TOP_MODE_ANALOG);
	NOP4;

	LL_ADC_REG_StartConversionSWStart(ADC1);
	while (u8DMA_ADCtransferStatus != DMA_TRANSFER_FINISHED)
	{
	}
	u8DMA_ADCtransferStatus = DMA_NO_TRANSFER;
	MODIFY_REG(TOP_PORT->CRL, TOP_CRL_MASK, TOP_MODE_OUTPUT);
	MODIFY_REG(TOP_PORT->ODR, TOP_PINS_MASK, TOP_LOW_LEVEL); /* Set Low Level to Top pins */
}

void CapSens_ApiGetSensorsValue(uint16_t *pu16Destination)
{
	for (uint8_t i = 0; i < SENSORS_AMOUNT; i++)
	{
		pu16Destination[i] = au16SensorsValue[i];
	}
}

static void DMA_Init(void)
{
	/* Configuration of NVIC 							*/
	/* Configure NVIC to enable DMA interruptions		*/
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_CAP_DMA_PRIORITY);  /* DMA IRQ lower priority than ADC IRQ */
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);

	/* Configuration of DMA 				*/
	/* Enable the peripheral clock of DMA   */
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

	/* Configure the DMA transfer */
	/*  - DMA transfer in circular mode to match with ADC configuration:        */
	/*    DMA unlimited requests.                                               */
	/*  - DMA transfer from ADC without address increment.                      */
	/*  - DMA transfer to memory with address increment.                        */
	/*  - DMA transfer from ADC by half-word to match with ADC configuration:   */
	/*    ADC resolution 12 bits.                                               */
	/*  - DMA transfer to memory by half-word to match with ADC conversion data */
	/*    buffer variable type: half-word.                                      */
	LL_DMA_ConfigTransfer(DMA1,
						  DMA_CHANNEL_ADC,
						  LL_DMA_DIRECTION_PERIPH_TO_MEMORY |
						  LL_DMA_MODE_CIRCULAR              |
						  LL_DMA_PERIPH_NOINCREMENT         |
						  LL_DMA_MEMORY_INCREMENT           |
						  LL_DMA_PDATAALIGN_HALFWORD        |
						  LL_DMA_MDATAALIGN_HALFWORD        |
						  LL_DMA_PRIORITY_HIGH               );

	/* Set DMA transfer addresses of source and destination */
	LL_DMA_ConfigAddresses(DMA1,
						   DMA_CHANNEL_ADC,
						   LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA),
						   (uint32_t)au16SensorsValue,
						   LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

	/* Set DMA transfer size */
	LL_DMA_SetDataLength(DMA1,
						 DMA_CHANNEL_ADC,
						 (uint32_t)SENSORS_AMOUNT);

	/* Enable DMA transfer interruption: transfer complete */
	LL_DMA_EnableIT_TC(DMA1, DMA_CHANNEL_ADC);

	/* Activation of DMA 						*/
	/* Enable the DMA transfer 					*/
	LL_DMA_EnableChannel(DMA1, DMA_CHANNEL_ADC);
}

static void ADC_Init(void)
{
	MODIFY_REG(TOP_PORT->CRL, TOP_CRL_MASK, TOP_MODE_ANALOG);

	NVIC_SetPriority(ADC1_IRQn, NVIC_CAP_ADC_PRIORITY);
	NVIC_EnableIRQ(ADC1_IRQn);

	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);

	LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_2);

	LL_ADC_SetSequencersScanMode(ADC1, LL_ADC_SEQ_SCAN_ENABLE);

    LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);

    LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);

    LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_UNLIMITED);

    LL_ADC_REG_SetSequencerLength(ADC1, LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS);

    LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_3);
    LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_2, LL_ADC_CHANNEL_4);
    LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_3, LL_ADC_CHANNEL_5);
    LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_4, LL_ADC_CHANNEL_6);
    LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_5, LL_ADC_CHANNEL_7);

    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_3, LL_ADC_SAMPLINGTIME_41CYCLES_5);
    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_4, LL_ADC_SAMPLINGTIME_41CYCLES_5);
    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_5, LL_ADC_SAMPLINGTIME_41CYCLES_5);
    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_6, LL_ADC_SAMPLINGTIME_41CYCLES_5);
    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_7, LL_ADC_SAMPLINGTIME_41CYCLES_5);

  /* Configuration of ADC interruptions									*/
  /* Enable interruption ADC group regular end of sequence conversions  */
  LL_ADC_EnableIT_EOS(ADC1);
}

static void ADC_Activate(void)
{
    /* Enable ADC */
    LL_ADC_Enable(ADC1);

    NOP8;

    /* Run ADC self calibration */
    LL_ADC_StartCalibration(ADC1);

    while (LL_ADC_IsCalibrationOnGoing(ADC1) != 0)
    {
    };
}

void DMA_AdcTransferComplete_Callback(void)
{
	u8DMA_ADCtransferStatus = DMA_TRANSFER_FINISHED;
}
