/*
 * scheduler.c
 *
 *  Created on: 30 мая 2020 г.
 *      Author: 1311985
 */

#include "scheduler.h"
#include "callbacks.h"

/** u8SystemCounter -- indicates amount of SystemTicks from certain point.								*/
__IO uint8_t u8SystemCounter;

/* atTasks[] -- contains all tasks and their parameters. Tasks are ordered by their period and offset.  */
/* It means that task with smaller period and offset would have smaller index.						    */
task_t atTasks[TASKS_AMOUNT];

/*	vTaskInit -- is auxiliary function to initialize "atTasks" for one task per call.					*/
void vTaskInit(void *pvRoutine, uint8_t u8Period, uint8_t u8Offset);


void vScheduler_Init(void)
{
	vTaskInit(vTask_2ms, 	2,  0);
	vTaskInit(vTask_10ms_0, 10, 0);
	vTaskInit(vTask_10ms_1, 10, 1);
	vTaskInit(vTask_20ms, 	20, 0);
}

void vScheduler(void)
{
	/* Contain last value of u8SystemCounter in order to check if "Counter" was iterated.				*/
	static uint8_t u8LastCounterValue = 0;
	/* Below variables are created in sake of clearance. They take period/offset value of some task to 	*/
	/* figure out if period for this task lasted.														*/
	uint8_t u8TaskPeriod = 0;
	uint8_t u8TaskOffset = 0;


	vTask_Init();

	while(1)
	{
		u8SystemCounter = 0;
		while (u8SystemCounter < 10)
		{
			u8LastCounterValue = u8SystemCounter;
			atTasks[0].pfRoutine();
			for (uint8_t u8TaskIndex = 1; u8TaskIndex < TASKS_AMOUNT; u8TaskIndex++)
			{
				u8TaskPeriod = atTasks[u8TaskIndex].u8Period;
				u8TaskOffset = atTasks[u8TaskIndex].u8Offset;
				if (IS_PERIOD_LAST(u8SystemCounter, u8TaskPeriod, u8TaskOffset) == 1)
				{
					atTasks[u8TaskIndex].pfRoutine();
				}
			}
			while (u8LastCounterValue == u8SystemCounter)
			{
			};
		}
	}
}

void vTaskInit(void *pvRoutine, uint8_t u8Period, uint8_t u8Offset)
{
	static uint8_t u8Index = 0;

	if (u8Index < TASKS_AMOUNT)
	{
		atTasks[u8Index].pfRoutine = pvRoutine;
		atTasks[u8Index].u8Period  = u8Period / SYS_TICK_PERIOD;
		atTasks[u8Index].u8Offset  = u8Offset;
	}

	u8Index++;
}

void vScheduler_SysTick_Callback(void)
{
	u8SystemCounter++;
}
