/*
 * callbacks.h
 *
 *  Created on: 30 мая 2020 г.
 *      Author: 1311985
 */

#ifndef INC_CALLBACKS_H_
#define INC_CALLBACKS_H_

void vScheduler_SysTick_Callback(void);

void DMA_AdcTransferComplete_Callback(void);

void DMA_UsartTransmitComplete_Callback(void);

void DMA_UsartReceiveComplete_Callback(void);

#endif /* INC_CALLBACKS_H_ */
