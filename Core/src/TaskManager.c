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


void vTask_Init(void)
{
	CapSens_InitRoutine();
	Debug_Init();
}

void vTask_2ms(void)
{
	CapSens_ChargeRoutine_2ms();
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
