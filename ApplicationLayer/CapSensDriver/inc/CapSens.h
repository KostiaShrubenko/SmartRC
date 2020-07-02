/*
 * CapSens.h
 *
 *  Created on: 15 мая 2020 г.
 *      Author: 1311985
 */

#ifndef CAPSENSDRIVER_INC_CAPSENS_H_
#define CAPSENSDRIVER_INC_CAPSENS_H_

#include "main.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_adc.h"

/* ---------------------------------------------------------------------------------------- */
/*									GPIO Configuration macros 								*/
/* ---------------------------------------------------------------------------------------- */
/* All macros below have to be configured depending on specific solution. 					*/
/* Naming of macros:																		*/
/* -- Prefix "TOP" means configuration for pins which are connected to Capacitive sensor by */
/*	  by resistor and to Sampling Capacitor's pin from which would be measured voltage.		*/
/* -- Prefix "BOTTOM" means configuration for pins which are connected to another pin of 	*/
/*	  Sampling Capacitor.																	*/


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

/* Macros define which part of sensing schematic connected to which port.					 */
#define TOP_PORT	GPIOA
#define BOTTOM_PORT	GPIOB

/* Represent masks for setting high level on included pins by ODR register.					*/
#define TOP_PINS_MASK		((1 << PIN3) | (1 << PIN4) |\
							 (1 << PIN5) | (1 << PIN6) | (1 << PIN7))
#define BOTTOM_PINS_MASK	((1 << PIN0) | (1 << PIN1) | (1 << PIN2) |\
							 (1 << PIN10) | (1 << PIN11) | (1 << PIN12))

#define TOP_HIGH_LEVEL 		((1 << PIN3) | (1 << PIN4) |\
							 (1 << PIN5) | (1 << PIN6) | (1 << PIN7))
#define TOP_LOW_LEVEL  		0U
#define BOTTOM_LOW_LEVEL 	0U


/* Represent array of pins for initialization structure of LL_GPIO driver.					*/
#define TOP_PINS 	(LL_GPIO_PIN_2  | LL_GPIO_PIN_3 | LL_GPIO_PIN_4  |\
					 LL_GPIO_PIN_5  | LL_GPIO_PIN_6 | LL_GPIO_PIN_7)

#define BOTTOM_PINS (LL_GPIO_PIN_0  | LL_GPIO_PIN_1  | LL_GPIO_PIN_2  |\
					 LL_GPIO_PIN_10 | LL_GPIO_PIN_11 | LL_GPIO_PIN_12)


#define CRL_MASK							(GPIO_CRL_CNF0 | GPIO_CRL_MODE0)
#define PIN_MODE_FLOAT						(GPIO_CRL_CNF0_0)
#define PIN_MODE_ANALOG						0U
#define PIN_MODE_OUTPUT_PP					(GPIO_CRL_MODE0_1)
#define PIN_CRL_BITS 						4U

/* Macro to set mask for some pin depending on amount of bits which are reserved for one pin.*/
#define SET_PIN_MASK(pin, mask, pinbits) 	((mask) << ((pin) * (pinbits)))

#define PIN0_CRL_MASK	SET_PIN_MASK(PIN0, CRL_MASK, PIN_CRL_BITS)
#define PIN1_CRL_MASK	SET_PIN_MASK(PIN1, CRL_MASK, PIN_CRL_BITS)
#define PIN2_CRL_MASK	SET_PIN_MASK(PIN2, CRL_MASK, PIN_CRL_BITS)
#define PIN3_CRL_MASK	SET_PIN_MASK(PIN3, CRL_MASK, PIN_CRL_BITS)
#define PIN4_CRL_MASK	SET_PIN_MASK(PIN4, CRL_MASK, PIN_CRL_BITS)
#define PIN5_CRL_MASK	SET_PIN_MASK(PIN5, CRL_MASK, PIN_CRL_BITS)
#define PIN6_CRL_MASK	SET_PIN_MASK(PIN6, CRL_MASK, PIN_CRL_BITS)
#define PIN7_CRL_MASK	SET_PIN_MASK(PIN7, CRL_MASK, PIN_CRL_BITS)
#define PIN8_CRH_MASK	SET_PIN_MASK(PIN8 - 8, CRL_MASK, PIN_CRL_BITS)
#define PIN9_CRH_MASK	SET_PIN_MASK(PIN9 - 8, CRL_MASK, PIN_CRL_BITS)
#define PIN10_CRH_MASK	SET_PIN_MASK(PIN10 - 8, CRL_MASK, PIN_CRL_BITS)
#define PIN11_CRH_MASK	SET_PIN_MASK(PIN11 - 8, CRL_MASK, PIN_CRL_BITS)
#define PIN12_CRH_MASK	SET_PIN_MASK(PIN12 - 8, CRL_MASK, PIN_CRL_BITS)
#define PIN13_CRH_MASK	SET_PIN_MASK(PIN13 - 8, CRL_MASK, PIN_CRL_BITS)
#define PIN14_CRH_MASK	SET_PIN_MASK(PIN14 - 8, CRL_MASK, PIN_CRL_BITS)
#define PIN15_CRH_MASK	SET_PIN_MASK(PIN15 - 8, CRL_MASK, PIN_CRL_BITS)


#define BOTTOM_CRL_MASK 		(PIN0_CRL_MASK 	   | PIN1_CRL_MASK     | PIN2_CRL_MASK)
#define BOTTOM_CRH_MASK 		(PIN10_CRH_MASK    | PIN11_CRH_MASK    | PIN12_CRH_MASK |\
								 PIN13_CRH_MASK    | PIN14_CRH_MASK)

#define BOTTOM_CRL_MODE_FLOAT 	(GPIO_CRL_CNF0_0   | GPIO_CRL_CNF1_0   | GPIO_CRL_CNF2_0)
#define BOTTOM_CRH_MODE_FLOAT	(GPIO_CRH_CNF10_0  | GPIO_CRH_CNF11_0  | GPIO_CRH_CNF12_0 |\
								 GPIO_CRH_CNF13_0  | GPIO_CRH_CNF14_0)
#define BOTTOM_CRL_MODE_OUTPUT 	(GPIO_CRL_MODE0_1  | GPIO_CRL_MODE1_1  | GPIO_CRL_MODE2_1)
#define BOTTOM_CRH_MODE_OUTPUT	(GPIO_CRH_MODE10_1 | GPIO_CRH_MODE11_1 | GPIO_CRH_MODE12_1 |\
								 GPIO_CRH_MODE13_1 | GPIO_CRH_MODE14_1)
#define BOTTOM_CRL_MODE_ANALOG	 PIN_MODE_ANALOG
#define BOTTOM_CRH_MODE_ANALOG	 PIN_MODE_ANALOG


#define TOP_CRL_MASK 	(PIN2_CRL_MASK    | PIN3_CRL_MASK 	 | PIN4_CRL_MASK |\
						 PIN5_CRL_MASK    | PIN6_CRL_MASK    | PIN7_CRL_MASK)
#define TOP_MODE_FLOAT 	(GPIO_CRL_CNF2_0  | GPIO_CRL_CNF3_0  | GPIO_CRL_CNF4_0 |\
						 GPIO_CRL_CNF5_0  | GPIO_CRL_CNF6_0  | GPIO_CRL_CNF7_0)
#define TOP_MODE_OUTPUT (GPIO_CRL_MODE2_0 | GPIO_CRL_MODE3_0 | GPIO_CRL_MODE4_0 |\
						 GPIO_CRL_MODE5_0 | GPIO_CRL_MODE6_0 | GPIO_CRL_MODE7_0)
#define	TOP_MODE_ANALOG	 PIN_MODE_ANALOG

#define TOP_CLK_ENABLE()	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA)
#define BOTTOM_CLK_ENABLE()	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB)

/* ######################################################################################## */

/* Set how many times capacitive sensors have to be charged and discharged to sampling 		*/
/* capacitor.																				*/
#define CHARGE_CYCLES	75U

/* Set which channel of DMA has to be used as one to transfer ADC data to specific memory.	*/
#define DMA_CHANNEL_ADC LL_DMA_CHANNEL_1

/* Following macros indicate in which state DMA transfer currently is.						*/
#define DMA_NO_TRANSFER 		0
#define DMA_TRANSFER_FINISHED	1




/**
 * @brief	Initializes all needed peripherals to perform capacitive sensing.
 * 			Should be included in "vTask_Init".
 *
 * @param 	None
 * @retval	None
 */
void CapSens_InitRoutine(void);

/**
 * @brief	Perform measurements of capacitive sensors' relative capacitance.
 * 			Should be included in task with period 2 (milliseconds).
 *
 * @param	None
 * @retval  None
 */
void CapSens_ChargeRoutine_2ms(void);




#endif /* CAPSENSDRIVER_INC_CAPSENS_H_ */
