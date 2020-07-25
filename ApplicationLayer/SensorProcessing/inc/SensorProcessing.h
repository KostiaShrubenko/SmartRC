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
#include "SensorProcessing_Datatypes.h"

#define SENSOR_0_INDEX	0
#define SENSOR_1_INDEX	1
#define SENSOR_2_INDEX	2
#define SENSOR_3_INDEX	3
#define SENSOR_4_INDEX	4


#define FACTOR	16

#define PRE_CALIBRATION_CYCLES 	30
#define CALIBRATION_CYCLES 		10
#define IDLENESS_CYCLES			10

#define TOUCH_DELTA_THRESHOLD 2500
#define IDLE_DELTA_THRESHOLD 100
#define TOUCH_DERIVATIVE_THRESHOLD 60
#define DERIVATIVE_ZERO_THRESHOLD 5

#define ABOVE_ZERO 1
#define BELOW_ZERO -1


#define FILTER_BUFFER_SIZE 20



void SensorProcessing_Routine_2ms(void);

#endif /* SENSORPROCESSING_INC_SENSORPROCESSING_H_ */
