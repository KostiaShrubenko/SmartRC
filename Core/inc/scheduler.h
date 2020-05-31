/*
 * scheduler.h
 *
 *  Created on: 30 мая 2020 г.
 *      Author: 1311985
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "stm32f1xx_ll_system.h"

#define SYS_TICK_PERIOD	2 /* (milliseconds) period of system clock. It has to be set by function "LL_Init1msTick()" */
#define TASKS_AMOUNT	4 /* Amount of tasks for Scheduler to handle.												*/

/* IS_PERIOD_LAST -- figures out if time has come for task, which parameters are passed here, to be called.			*/
/* It returns !one! if time has come and !zero! if not.																*/
#define IS_PERIOD_LAST(counter, period, offset) ((((int8_t)(counter) - (int8_t)(offset)) % (period)) == 0)

/** @struct task_t
 * 	@brief This type of structure represents all parameters of single task which is needed to handle it by Scheduler.
 *
 * 	@var task_t::u8Period
 * 		Indicates an amount of time after which task has to be repeated.
 * 	@var task_t::u8Offset
 * 		Indicates iteration offset from start point of Scheduler. For example we have two task with period 10(ms) one
 * 		has offset 0 and another 1. Then when scheduler starts it executes task with 0 offset and only
 * 		on the next iteration it executes task with offset 1.
 * 	@var task_t::pfRoutine
 * 		Is pointer to implementation of task.
 */
typedef struct {
	uint8_t u8Period;
	uint8_t u8Offset;
	void (*pfRoutine)(void);
} task_t;


/*										Rules of Task Naming								*/
/* 	-- Each task has to be named with prefix "vTask" where 'v' means						*/
/* 	   that function has return type "void".												*/
/*	-- Each task has (_) underscore after prefix.											*/
/*	-- After underscore should be followed numerical value of task repetition period 		*/
/*	   e.g. "2ms"																			*/
/*	-- If there are several tasks with same period and different offset then a following	*/
/*	   ending has to be added: it represents iteration offset of corresponding task.		*/

/* ---------------------------------------------------------------------------------------- */
/*                                      Tasks Declarations									*/

void vTask_Init(void);

void vTask_2ms(void);

void vTask_10ms_0(void);

void vTask_10ms_1(void);

void vTask_20ms(void);

/* ######################################################################################## */

/* ---------------------------------------------------------------------------------------- */
/*                         Scheduler's Functions Declarations								*/

/**
 * @brief This function adds all existing task to Scheduler. It has to be included in
 * "main()" after ClockInitialization.
 *
 * @note Developer has to include initialization of all tasks to this function by
 * his own in "scheduler.c", otherwise they will not be managed by Scheduler.
 *
 * @param 	None
 * @retval 	None
 */
void vScheduler_Init(void);

/**
 * @brief This function is itself Scheduler. It has to be included in "main()" after
 * "vScheduler_Init".
 *
 * @note This function should *not* be modified.
 *
 * @param 	None
 * @retval 	None
 */
void vScheduler(void);

/* ######################################################################################## */

#endif /* INC_SCHEDULER_H_ */
