/*
 * SensorProcessing.c
 *
 *  Created on: 1 июн. 2020 г.
 *      Author: 1311985
 */

#include "SensorProcessing.h"

static SensorValues_t atSensors[SENSORS_AMOUNT];
static uint16_t au16RawValues[SENSORS_AMOUNT];

static uint8_t u8CalibrationCyclesCounter = CALIBRATION_CYCLES;
static uint16_t u16Offsets[SENSORS_AMOUNT];

static void CalculateDeltaValues(void);
static void FilterValuesByBuffer(void);
static void TakeDerivative(void);

void SensorProcessing_Routine_2ms(void)
{
	CapSens_ApiGetSensorsValue(au16RawValues);
	if (u8CalibrationCyclesCounter > 0)
	{
		for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
		{
			u16Offsets[u8SensorIndex] += au16RawValues[u8SensorIndex] / CALIBRATION_CYCLES;
		}
		u8CalibrationCyclesCounter--;
	}
	else
	{
		CalculateDeltaValues();
		FilterValuesByBuffer();
		TakeDerivative();
	}
}

static void CalculateDeltaValues(void)
{
	for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
	{
		atSensors[u8SensorIndex].i16DeltaValue = (au16RawValues[u8SensorIndex] - u16Offsets[u8SensorIndex]) * 10;
	}
}


static void FilterValuesByBuffer(void)
{
	static int16_t ai16FilterBuffer[SENSORS_AMOUNT][FILTER_BUFFER_SIZE];
	static int32_t ai32BufferSum[SENSORS_AMOUNT];
	static uint8_t u8PositionInBuffer = 0;
	static uint8_t u8IsBufferFilled = 0;

	for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
	{
		if (u8IsBufferFilled == 0)
		{
			ai32BufferSum[u8SensorIndex] += atSensors[u8SensorIndex].i16DeltaValue;
			ai16FilterBuffer[u8SensorIndex][u8PositionInBuffer] = atSensors[u8SensorIndex].i16DeltaValue;
		}
		else
		{
			ai32BufferSum[u8SensorIndex] -= ai16FilterBuffer[u8SensorIndex][u8PositionInBuffer];
			ai32BufferSum[u8SensorIndex] += atSensors[u8SensorIndex].i16DeltaValue;
			ai16FilterBuffer[u8SensorIndex][u8PositionInBuffer] = atSensors[u8SensorIndex].i16DeltaValue;
			atSensors[u8SensorIndex].i16FilteredValue = ai32BufferSum[u8SensorIndex] / FILTER_BUFFER_SIZE;
		}
	}
	u8PositionInBuffer++;
	if (u8PositionInBuffer == FILTER_BUFFER_SIZE)
	{
		if (u8IsBufferFilled == 0)
		{
			u8IsBufferFilled = 1;
		}
		u8PositionInBuffer = 0;
	}

}

static void TakeDerivative(void)
{
	static int16_t LastFilteredValues[SENSORS_AMOUNT];
	for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
	{
		atSensors[u8SensorIndex].i16DerivativeValue = (atSensors[u8SensorIndex].i16FilteredValue - LastFilteredValues[u8SensorIndex]) * 10;
		LastFilteredValues[u8SensorIndex] = atSensors[u8SensorIndex].i16FilteredValue;
	}
}


void SensorProcessing_ApiGetDeltas(int16_t *pi16Destination)
{
	for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
	{
		pi16Destination[u8SensorIndex] = atSensors[u8SensorIndex].i16DeltaValue;
	}
}

void SensorProcessing_ApiGetFilteredValues(int16_t *pi16Destination)
{
	for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
	{
		pi16Destination[u8SensorIndex] = atSensors[u8SensorIndex].i16FilteredValue;
	}
}


int8_t SensorProcessing_ApiGetSensorValues(SensorValues_t *ptDestination, uint8_t u8SensorIndex)
{
	int8_t i8ReturnValue = 0;
	if (u8SensorIndex >= SENSORS_AMOUNT)
	{
		i8ReturnValue = ERROR;
	}
	else
	{
		pi16Destination = &atSensors[u8SensorIndex];
		i8ReturnValue = SUCCESS;
	}
	return i8ReturnValue;
}
