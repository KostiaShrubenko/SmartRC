/*
 * SensorProcessing_Api.h
 *
 *  Created on: 1 июн. 2020 г.
 *      Author: 1311985
 */

#ifndef SENSORPROCESSING_INC_SENSORPROCESSING_API_H_
#define SENSORPROCESSING_INC_SENSORPROCESSING_API_H_

#define ALL_SENSORS 0
#define SENSOR_0	0
#define SENSOR_1	1
#define SENSOR_2	2
#define SENSOR_3	3
#define SENSOR_4	4
#define SENSOR_5	5

void SensorProcessing_ApiGetDeltas(int16_t *pi16Destination);

void SensorProcessing_ApiGetFilteredValues(int16_t *pi16Destination);

int16_t SensorProcessing_ApiGetSensorValues(int16_t *pi16Destination, uint8_t u8SensorIndex);

#endif /* SENSORPROCESSING_INC_SENSORPROCESSING_API_H_ */
