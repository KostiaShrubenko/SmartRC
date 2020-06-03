/*
 * SensorProcessing.h
 *
 *  Created on: 1 июн. 2020 г.
 *      Author: 1311985
 */

#ifndef SENSORPROCESSING_INC_SENSORPROCESSING_H_
#define SENSORPROCESSING_INC_SENSORPROCESSING_H_

#include "main.h"
#include "CapSens_Api.h"

#define CALIBRATION_CYCLES 10


#define FILTER_BUFFER_SIZE 10


typedef struct {
	int16_t  i16DeltaValue;
	int16_t	 i16FilteredValue;
	int16_t  i16DerivativeValue;
} SensorValues_t;

void SensorProcessing_Routine_2ms(void);

#endif /* SENSORPROCESSING_INC_SENSORPROCESSING_H_ */
