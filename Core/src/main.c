/*
 * main.c
 *
 *  Created on: May 11, 2020
 *      Author: 1311985
 */


#include "main.h"
#include "scheduler.h"

void Init_Clock(void);


int main (void)
{
 	Init_Clock();
 	vScheduler_Init();
 	vScheduler();
	return 0;
}


/**
 * @brief Initialization of SystemClock source and 1ms SysTick.
 * @param None
 * @retval None
 */
void Init_Clock(void)
{
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

	/* 2ms config with HSI 8MHz*/
	LL_InitTick(HSI_VALUE, 500);
	LL_SetSystemCoreClock(HSI_VALUE);
}

/**
 * @brief Initialization of all GPIO.
 * @param None
 * @retval None
 */
//void Init_GPIO(void)
//{
//	LL_GPIO_InitTypeDef tGPIO_InitStructure; /* Structure to contain GPIOs configurations.	*/
//
//	PORTC_CLK_ENABLE();
//
//	tGPIO_InitStructure.Pin = LED_PIN | SIGNAL_PIN | LL_GPIO_PIN_12 | LL_GPIO_PIN_13 | LL_GPIO_PIN_14;
//	tGPIO_InitStructure.Mode = LL_GPIO_MODE_OUTPUT;
//	tGPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_LOW;
//	tGPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	tGPIO_InitStructure.Pull = LL_GPIO_PULL_DOWN;
//
//	LL_GPIO_Init(LED_PORT, &tGPIO_InitStructure);
//}
