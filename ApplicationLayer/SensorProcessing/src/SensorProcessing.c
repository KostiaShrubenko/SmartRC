/*
 * SensorProcessing.c
 *
 *  Created on: 1 июн. 2020 г.
 *      Author: 1311985
 */

#include "SensorProcessing.h"

StateMachine_t SM = {
	.u8PreCalibrationCounter = PRE_CALIBRATION_CYCLES,
	.u8CalibrationCounter = CALIBRATION_CYCLES,
	.tState = precalibration
};



#if DEBUG_MODE == ON
/* DEBUG VARIABLES */

static uint16_t au16FirstRawValues[CALIBRATION_CYCLES];

#endif /* DEBUG_MODE */


static void Calibration(void);
static void CalculateDeltaValues(void);
static void FilterValuesByBuffer(void);
static void TakeDerivative(void);

void SensorProcessing_Routine_2ms(void)
{
	CapSens_ApiGetSensorsValue(SM.au16RawValues);
	switch (SM.tState) {
	case precalibration:
		SM.u8PreCalibrationCounter--;
		if (SM.u8PreCalibrationCounter == 0)
		{
			SM.tState = calibration;
		}
		break;
	case calibration:
		Calibration();
		SM.u8CalibrationCounter--;
		if (SM.u8CalibrationCounter == 0)
		{
			SM.tState = bufferfilling;
		}
		break;
	case bufferfilling:
		CalculateDeltaValues();
		FilterValuesByBuffer();
		break;
	case processing:
		CalculateDeltaValues();
		FilterValuesByBuffer();
		TakeDerivative();
		break;
	default:
		break;
	}
}

static void Calibration(void)
{
	for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
	{
#if DEBUG_MODE == ON
		if (u8SensorIndex == 0)
		{
			au16FirstRawValues[CALIBRATION_CYCLES - SM.u8CalibrationCounter] = SM.au16RawValues[u8SensorIndex];
		}
#endif /* DEBUG_MODE */
		SM.u16Offsets[u8SensorIndex] += SM.au16RawValues[u8SensorIndex] * 10 / CALIBRATION_CYCLES;
		if (SM.u8CalibrationCounter == 1)
		{
			SM.u16Offsets[u8SensorIndex] /= 10;
		}
	}
}

static void CalculateDeltaValues(void)
{
	for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
	{
		SM.atSensors[u8SensorIndex].i16DeltaValue = (SM.au16RawValues[u8SensorIndex] - SM.u16Offsets[u8SensorIndex]) * 10;
	}
}


static void FilterValuesByBuffer(void)
{
	static int16_t ai16FilterBuffer[SENSORS_AMOUNT][FILTER_BUFFER_SIZE];
	static int32_t ai32BufferSum[SENSORS_AMOUNT];
	static uint8_t u8PositionInBuffer = 0;

	for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
	{
		if (SM.tState == bufferfilling)
		{
			ai32BufferSum[u8SensorIndex] += SM.atSensors[u8SensorIndex].i16DeltaValue;
			ai16FilterBuffer[u8SensorIndex][u8PositionInBuffer] = SM.atSensors[u8SensorIndex].i16DeltaValue;
		}
		else
		{
			ai32BufferSum[u8SensorIndex] -= ai16FilterBuffer[u8SensorIndex][u8PositionInBuffer];
			ai32BufferSum[u8SensorIndex] += SM.atSensors[u8SensorIndex].i16DeltaValue;
			ai16FilterBuffer[u8SensorIndex][u8PositionInBuffer] = SM.atSensors[u8SensorIndex].i16DeltaValue;
			SM.atSensors[u8SensorIndex].i16FilteredValue = ai32BufferSum[u8SensorIndex] / FILTER_BUFFER_SIZE;
		}
	}
	u8PositionInBuffer++;
	if (u8PositionInBuffer == FILTER_BUFFER_SIZE)
	{
		if (SM.tState == bufferfilling)
		{
			SM.tState = processing;
		}
		u8PositionInBuffer = 0;
	}
}

static void TakeDerivative(void)
{
	static int16_t LastFilteredValues[SENSORS_AMOUNT];
	for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
	{
		SM.atSensors[u8SensorIndex].i16DerivativeValue = (SM.atSensors[u8SensorIndex].i16FilteredValue - LastFilteredValues[u8SensorIndex]) * 10;
		LastFilteredValues[u8SensorIndex] = SM.atSensors[u8SensorIndex].i16FilteredValue;
	}
}

/* Debug API */
#if DEBUG_MODE == ON
void SensorProcessing_ApiGetCalibrationValues(uint16_t *pu16Destination)
{
	static uint8_t i = 0;
	pu16Destination[0] = au16FirstRawValues[i];
	i++;
	if (i == CALIBRATION_CYCLES)
	{
		i = 0;
	}
}
#endif /* DEBUG_MODE */

void SensorProcessing_ApiGetDeltas(int16_t *pi16Destination)
{
	for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
	{
		pi16Destination[u8SensorIndex] = SM.atSensors[u8SensorIndex].i16DeltaValue;
	}
}

void SensorProcessing_ApiGetFilteredValues(int16_t *pi16Destination)
{
	for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
	{
		pi16Destination[u8SensorIndex] = SM.atSensors[u8SensorIndex].i16FilteredValue;
	}
}

int8_t SensorProcessing_ApiGetSensorValues(int16_t *pi16Destination, uint8_t u8SensorIndex)
{
	pi16Destination[0] = SM.au16RawValues[u8SensorIndex];
	pi16Destination[1] = SM.atSensors[u8SensorIndex].i16DeltaValue;
	pi16Destination[2] = SM.atSensors[u8SensorIndex].i16FilteredValue;
	pi16Destination[3] = SM.atSensors[u8SensorIndex].i16DerivativeValue;

	return 0;
}
