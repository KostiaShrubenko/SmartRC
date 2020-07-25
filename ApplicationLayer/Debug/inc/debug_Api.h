/*
 * debug_Api.h
 *
 *  Created on: 25 июл. 2020 г.
 *      Author: 1311985
 */

#ifndef DEBUG_INC_DEBUG_API_H_
#define DEBUG_INC_DEBUG_API_H_

#include "debug.h"

/**
 * @brief	This function turns on 3 LEDs on board.
 *
 * @param	None
 * @retval	None
 */
__STATIC_INLINE void Debug_ApiSetLED(void)
{
	LL_GPIO_ResetOutputPin(LED_PORT, LED_PIN);
}

/**
 * @brief	This function turns off 3 LEDs on board.
 *
 * @param	None
 * @retval	None
 */
__STATIC_INLINE void Debug_ApiResetLED(void)
{
	LL_GPIO_SetOutputPin(LED_PORT, LED_PIN);
}

/**
 * @brief	This function change state of 3 LEDs on board.
 *
 * @param	None
 * @retval	None
 */
__STATIC_INLINE void Debug_ApiToggleLED(void)
{
	LL_GPIO_TogglePin(LED_PORT, LED_PIN);
}

#endif /* DEBUG_INC_DEBUG_API_H_ */
