/*
 * TaskManager.c
 *
 *  Created on: 30 мая 2020 г.
 *      Author: 1311985
 */

#include "main.h"
#include "scheduler.h"

#include "debug.h"
#include "debug_Api.h"
#include "CapSens.h"
#include "SensorProcessing.h"



void vTask_Init(void)
{
	CapSens_InitRoutine();
#if DEBUG_MODE == ON
	Debug_Init();
#endif /* DEBUG_MODE */
}

void vTask_2ms(void)
{
	//Debug_ApiSetLED();
	CapSens_ChargeRoutine_2ms();
	SensorProcessing_Routine_2ms();
#if DEBUG_MODE == ON
	Debug_Routine_2ms();
#endif /* DEBUG_MODE*/
	//Debug_ApiResetLED();
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
