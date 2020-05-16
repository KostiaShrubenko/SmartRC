/*
 * main.h
 *
 *  Created on: May 11, 2020
 *      Author: 1311985
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_


#include "Config.h"
#include "stm32f1xx.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_gpio.h"
#include "CapSens.h"


#define RCC_ERROR_NONE	0
#define RCC_ERROR 		1

#define LED_PIN				LL_GPIO_PIN_11
#define LED_PORT			GPIOB
#define SIGNAL_PIN			LL_GPIO_PIN_10
#define SIGNAL_PORT			GPIOB
#define PORTC_CLK_ENABLE()	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB)

__IO uint16_t u16Ticks;

__STATIC_INLINE void IncrementTicks_CallBack(void)
{
	u16Ticks++;
}

__STATIC_INLINE void ResetTickCounter(void)
{
	u16Ticks = 0;
}

#endif /* INC_MAIN_H_ */
