/*
 * SensorProcessing_Datatypes.h
 *
 *  Created on: 9 июл. 2020 г.
 *      Author: 1311985
 */

#ifndef SENSORPROCESSING_INC_SENSORPROCESSING_DATATYPES_H_
#define SENSORPROCESSING_INC_SENSORPROCESSING_DATATYPES_H_

#include "SensorProcessing.h"

/*------------------------------ API Datatypes ------------------------------*/

typedef enum {
	SensorState_Idle,
	SensorState_Touch
}SensorProcessing_SensorStates_t;

typedef struct {
	int16_t  						i16DeltaValue;
	int16_t	 						i16FilteredValue;
	int16_t  						i16DerivativeValue;
	SensorProcessing_SensorStates_t	tState;
} SensorProcessing_SensorValues_t;

/* ######################################################################### */

typedef enum {
	State_PreCalibration,
	State_Calibration,
	State_BufferFilling,
	State_Processing
} ProcessingStates_t;

typedef enum {
	TouchState_FingerReleased,
	TouchState_FingerDescent,
	TouchState_FingerTouch,
	TouchState_FingerLift
}TouchStates_t;


typedef struct {
	uint8_t u8PreCalibrationCounter;
	uint8_t u8CalibrationCounter;
	uint16_t au16OutputStateDuration[SENSORS_AMOUNT];
	uint16_t u16CyclesFromLastInteraction;
	ProcessingStates_t tState;
	TouchStates_t atSensorsTouchState[SENSORS_AMOUNT];
	uint16_t au16DeltaOffsets[SENSORS_AMOUNT];
	uint16_t au16RawValues[SENSORS_AMOUNT];
	SensorProcessing_SensorValues_t atSensorsOutput[SENSORS_AMOUNT];
} StateMachine_t;


#endif /* SENSORPROCESSING_INC_SENSORPROCESSING_DATATYPES_H_ */
