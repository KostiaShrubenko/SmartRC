/*
 * CapSens.h
 *
 *  Created on: 15 мая 2020 г.
 *      Author: 1311985
 */

#ifndef CAPSENSDRIVER_INC_CAPSENS_H_
#define CAPSENSDRIVER_INC_CAPSENS_H_

#include "CapSens_Config.h"
#include "main.h"

#define NOP2	__NOP(); __NOP()
#define NOP4	NOP2; NOP2
#define NOP6	NOP4; NOP2
#define NOP8	NOP4; NOP4
#define NOP16	NOP8; NOP8
#define NOP32	NOP16; NOP16
#define NOP64 	NOP32; NOP32

#define PIN0	0
#define PIN1	1
#define PIN2	2
#define PIN3	3
#define PIN4	4
#define PIN5	5
#define PIN6	6
#define PIN7	7
#define PIN8	8
#define PIN9    9
#define PIN10   10
#define PIN11   11
#define PIN12   12
#define PIN13   13
#define PIN14   14
#define PIN15   15

#define TOP_HIGH_LEVEL ( (1 << PIN1) | (1 << PIN2) | (1 << PIN3) | (1 << PIN4) | (1 << PIN5) | (1 << PIN6) )
#define TOP_LOW_LEVEL	0U
#define BOTTOM_LOW_LEVEL 	0U

#define TOP_PORT	GPIOA
#define BOTTOM_PORT	GPIOB

#define TOP_PINS 	(	LL_GPIO_PIN_1  | LL_GPIO_PIN_2  | LL_GPIO_PIN_3 |\
						LL_GPIO_PIN_4  | LL_GPIO_PIN_5  | LL_GPIO_PIN_6 )

#define BOTTOM_PINS 	(	LL_GPIO_PIN_0  | LL_GPIO_PIN_1  | LL_GPIO_PIN_2 |\
							LL_GPIO_PIN_12 | LL_GPIO_PIN_13 | LL_GPIO_PIN_14)

#define PIN_CRL_MASK		(GPIO_CRL_CNF0 | GPIO_CRL_MODE0)
#define PIN_MODE_FLOAT		(GPIO_CRL_CNF0_0)
#define PIN_MODE_ANALOG
#define PIN_MODE_OUTPUT_PP	(GPIO_CRL_MODE0_1)
#define PIN_CRL_BITS 	4U


#define BOTTOM_CONFIG_MASK ((GPIO_CRL_CNF0 | GPIO_CRL_MODE0) << (0U * 4U))
#define BOTTOM_MODE_FLOAT 	(GPIO_CRL_CNF0_0)
#define BOTTOM_MODE_OUTPUT 	(GPIO_CRL_MODE0_1)

#define TOP_CONFIG_MASK ((GPIO_CRL_CNF0 | GPIO_CRL_MODE0) << (6U * 4U))
#define TOP_MODE_FLOAT (GPIO_CRL_CNF6_0)
#define TOP_MODE_OUTPUT (GPIO_CRL_MODE6_1)

#define TOP_CLK_ENABLE()	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA)
#define BOTTOM_CLK_ENABLE()	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB)

void InitRoutine(void);
void ChargeRoutine(void);



#endif /* CAPSENSDRIVER_INC_CAPSENS_H_ */
