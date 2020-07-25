/*
 * SensorProcessing_Api.h
 *
 *  Created on: 1 июн. 2020 г.
 *      Author: 1311985
 */

#ifndef SENSORPROCESSING_INC_SENSORPROCESSING_API_H_
#define SENSORPROCESSING_INC_SENSORPROCESSING_API_H_

#include "SensorProcessing_Datatypes.h"

#define ALL_SENSORS 0
#define SENSOR_0	0
#define SENSOR_1	1
#define SENSOR_2	2
#define SENSOR_3	3
#define SENSOR_4	4


#if DEBUG_MODE == ON
/* --------------------------------- DEBUG API ---------------------------------- */
/* Designed to retreat additional values.										  */

void SensorProcessing_ApiGetCalibrationValues(uint16_t *pu16Destination);

#endif /* DEBUG_MODE */

/**
 * @brief Retrieve delta values of each capacitive sensor.
 *
 * @param pi16Destination Pointer to place where to store delta values.
 *
 * @retval None
 */
void SensorProcessing_ApiGetDeltas(int16_t *pi16Destination);

/**
 * @brief Retrieve filtered values of each sensor.
 *
 * @param pi16Destination Pointer to place where to store filtered values.
 */
void SensorProcessing_ApiGetFilteredValues(int16_t *pi16Destination);

/**
 * @brief Retrieve all evaluated values for one sensor.
 *
 * @param pi16Destination Pointer to place where to store evaluated values of sensor.
 * @param u8SensorIndex Index of sensor whose values developer wants to retrieve.
 *
 * @retval Makes to know whether values retrieved or there is no possibility to do that.
 *
 */
int8_t SensorProcessing_ApiGetSensorValues(SensorProcessing_SensorValues_t **ptDestination, uint8_t u8SensorIndex);

#endif /* SENSORPROCESSING_INC_SENSORPROCESSING_API_H_ */
