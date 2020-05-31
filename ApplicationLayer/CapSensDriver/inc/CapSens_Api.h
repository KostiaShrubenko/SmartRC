/*
 * CapSens_Api.h
 *
 *  Created on: 15 мая 2020 г.
 *      Author: 1311985
 */

#ifndef CAPSENSDRIVER_INC_CAPSENS_API_H_
#define CAPSENSDRIVER_INC_CAPSENS_API_H_

/**
 * @brief Gets value measured by ADC of each capacitive sensor.
 *
 * @param 	pu16Destination Pointer to desired place to store sensors' value.
 * @retval 	None
 */
void CapSens_ApiGetSensorsValue(uint16_t *pu16Destination);

#endif /* CAPSENSDRIVER_INC_CAPSENS_API_H_ */
