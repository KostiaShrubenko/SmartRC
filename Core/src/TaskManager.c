/*
 * TaskManager.c
 *
 *  Created on: 30 мая 2020 г.
 *      Author: 1311985
 */

#include "stm32f1xx.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_gpio.h"
#include "scheduler.h"


void vTask_Init(void)
{
	CapSens_InitRoutine();
}

void vTask_2ms(void)
{
	CapSens_ChargeRoutine_2ms();
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
