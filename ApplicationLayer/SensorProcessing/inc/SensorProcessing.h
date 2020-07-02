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

#define PRE_CALIBRATION_CYCLES 30
#define CALIBRATION_CYCLES 10


#define FILTER_BUFFER_SIZE 10

typedef enum {
	precalibration,
	calibration,
	bufferfilling,
	processing
} SensorProcessing_States_t;

typedef struct {
	int16_t  i16DeltaValue;
	int16_t	 i16FilteredValue;
	int16_t  i16DerivativeValue;
} SensorValues_t;

typedef struct {
	uint8_t u8PreCalibrationCounter;
	uint8_t u8CalibrationCounter;
	SensorProcessing_States_t tState;
	uint16_t u16Offsets[SENSORS_AMOUNT];
	uint16_t au16RawValues[SENSORS_AMOUNT];
	SensorValues_t atSensors[SENSORS_AMOUNT];
} StateMachine_t;

void SensorProcessing_Routine_2ms(void);

#endif /* SENSORPROCESSING_INC_SENSORPROCESSING_H_ */
