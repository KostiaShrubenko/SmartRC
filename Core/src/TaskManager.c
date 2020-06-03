/*
 * TaskManager.c
 *
 *  Created on: 30 мая 2020 г.
 *      Author: 1311985
 */

#include "main.h"
#include "scheduler.h"

#include "debug.h"
#include "CapSens.h"
#include "SensorProcessing.h"


void vTask_Init(void)
{
	CapSens_InitRoutine();
	Debug_Init();
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_13, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_13, LL_GPIO_OUTPUT_PUSHPULL);
}

void vTask_2ms(void)
{
	CapSens_ChargeRoutine_2ms();
	LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
	SensorProcessing_Routine_2ms();
	LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
	Debug_Routine_2ms();
}

void vTask_10ms_0(void)
{

}

void vTask_10ms_1(void)
{

}

void vTask_20ms(void)
{

}
