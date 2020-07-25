/*
 * main.h
 *
 *  Created on: May 11, 2020
 *      Author: 1311985
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_



#include "stm32f1xx.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_it.h"
#include "string.h"
#include "Config.h"


#define NOP2	__NOP(); __NOP()
#define NOP4	NOP2; NOP2
#define NOP8	NOP4; NOP4

#define ERROR	0
#define SUCCESS	1

#define YES		1
#define NO		0

#define TRUE	1
#define FALSE	0

#define FINISHED 	1
#define IN_PROGRESS	0




#endif /* INC_MAIN_H_ */
