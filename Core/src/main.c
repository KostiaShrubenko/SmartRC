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

