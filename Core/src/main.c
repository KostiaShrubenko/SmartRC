/*
 * main.c
 *
 *  Created on: May 11, 2020
 *      Author: 1311985
 */


#include "main.h"

void Init_Clock(void);
void Init_GPIO(void);


int main (void)
{
 	Init_Clock();
	//Init_GPIO();
 	InitRoutine();
	while (1)
	{
		ChargeRoutine();
		LL_mDelay(100);
		//LL_GPIO_WriteOutputPort(GPIOB, 0b0111110000000000);
		//LL_GPIO_WriteOutputPort(GPIOB, 0b0000000000000000);
	}
	return 0;
}


/**
 * @brief Initialization of SystemClock source and 1ms SysTick.
 * @param None
 * @retval None
 */
void Init_Clock(void)
{
	 /* Main PLL configuration and activation */
//	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2, LL_RCC_PLL_MUL_16);
//
//	LL_RCC_PLL_Enable();
//	while(LL_RCC_PLL_IsReady() != 1)
//	{
//	};
//
//	LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
//	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
//	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
//	{
//	};

	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

	/* 1ms config with HSI 8MHz*/
	LL_Init1msTick(8000000);//HSI_VALUE);
//	LL_SetSystemCoreClock(8000000);
}

/**
 * @brief Initialization of all GPIO.
 * @param None
 * @retval None
 */
void Init_GPIO(void)
{
	LL_GPIO_InitTypeDef tGPIO_InitStructure; /* Structure to contain GPIOs configurations.	*/

	PORTC_CLK_ENABLE();

	tGPIO_InitStructure.Pin = LED_PIN | SIGNAL_PIN | LL_GPIO_PIN_12 | LL_GPIO_PIN_13 | LL_GPIO_PIN_14;
	tGPIO_InitStructure.Mode = LL_GPIO_MODE_OUTPUT;
	tGPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_LOW;
	tGPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	tGPIO_InitStructure.Pull = LL_GPIO_PULL_DOWN;

	LL_GPIO_Init(LED_PORT, &tGPIO_InitStructure);
}
