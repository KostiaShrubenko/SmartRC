/*
 * SensorProcessing.c
 *
 *  Created on: 1 июн. 2020 г.
 *      Author: 1311985
 */

#include "SensorProcessing_Datatypes.h"
#include "SensorProcessing.h"
#include "SensorProcessing_Api.h"

static StateMachine_t SM = {
	.u8PreCalibrationCounter = PRE_CALIBRATION_CYCLES,
	.u8CalibrationCounter = CALIBRATION_CYCLES,
	.tState = State_PreCalibration,
};

uint8_t u8CalibrationState = FINISHED;


#if DEBUG_MODE == ON
/* DEBUG VARIABLES */

static uint16_t au16FirstRawValues[CALIBRATION_CYCLES];

#endif /* DEBUG_MODE */

static uint8_t IsCalibrationAllowed(void);
static uint8_t Calibration(void);
static void CalculateDeltaValues(void);
static void FilterValuesByBuffer(void);
static void TakeDerivative(void);
static void EvaluateTouch(void);

void SensorProcessing_Routine_2ms(void)
{
	CapSens_ApiGetSensorsValue(SM.au16RawValues);
	switch (SM.tState) {
	case State_PreCalibration:
		SM.u8PreCalibrationCounter--;
		if (SM.u8PreCalibrationCounter == 0)
		{
			SM.tState = State_Calibration;
			//SM.tState = State_BufferFilling;
		}
		break;
	case State_Calibration:
		if (Calibration() == FINISHED)
		{
			SM.tState = State_BufferFilling;
		}
		break;
	case State_BufferFilling:
		CalculateDeltaValues();
		FilterValuesByBuffer();
		break;
	case State_Processing:
		CalculateDeltaValues();
		FilterValuesByBuffer();
		TakeDerivative();
		EvaluateTouch();
		if (IsCalibrationAllowed() == YES || u8CalibrationState == IN_PROGRESS)
		{
			u8CalibrationState = Calibration();
		}
		break;
	default:
		break;
	}
}

static uint8_t IsCalibrationAllowed(void)
{
	uint8_t u8ReturnValue = NO;

	if (SM.u16CyclesFromLastInteraction >= IDLENESS_CYCLES)
	{
		u8ReturnValue = YES;
	}
	else
	{
		u8ReturnValue = NO;
	}

	return u8ReturnValue;
}

static uint8_t RemoveElementOfArray(uint8_t au8Array[], uint8_t *u8Length, uint8_t u8Value)
{
	uint8_t u8ReturnValue = ERROR;
	uint8_t u8Index;

	for (u8Index = 0; u8Index < *u8Length && au8Array[u8Index] == u8Value; u8Index++)
	{
	};
	if (u8Index != *u8Length)
	{
		for (u8Index; u8Index < (*u8Length - 1); u8Index++)
		{
			au8Array[u8Index] = au8Array[u8Index + 1];
		}
		(*u8Length)--;
		u8ReturnValue = SUCCESS;
	}
	else
	{
		u8ReturnValue = ERROR;
	}

	return u8ReturnValue;
}

static uint8_t Calibration(void)
{
	static uint32_t au32CalibrationBuffer[SENSORS_AMOUNT];
	static uint8_t u8AmountOfSensors2Calibrate;
	static uint8_t au8Sensors2Calibrate[SENSORS_AMOUNT];
	uint8_t u8CurrentSensor = 0;
	uint8_t u8ReturnValue = IN_PROGRESS;

	if (SM.u8CalibrationCounter == CALIBRATION_CYCLES)
	{
		SM.u8CalibrationCounter = 0;
		memset(au32CalibrationBuffer, 0, sizeof(au32CalibrationBuffer));
		for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
		{
			au8Sensors2Calibrate[u8SensorIndex] = u8SensorIndex;
		}
		u8AmountOfSensors2Calibrate = SENSORS_AMOUNT;
	}


	for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
	{
		if (SM.atSensorsOutput[u8SensorIndex].i16DerivativeValue > ABOVE_ZERO * DERIVATIVE_ZERO_THRESHOLD ||
			SM.atSensorsOutput[u8SensorIndex].i16DerivativeValue < BELOW_ZERO * DERIVATIVE_ZERO_THRESHOLD)
		{
			(void)RemoveElementOfArray(au8Sensors2Calibrate, &u8AmountOfSensors2Calibrate, u8SensorIndex);
		}
	}

	SM.u8CalibrationCounter++;

	for (uint8_t u8I = 0; u8I < u8AmountOfSensors2Calibrate; u8I++)
	{
		u8CurrentSensor = au8Sensors2Calibrate[u8I];
		au32CalibrationBuffer[u8CurrentSensor] += (SM.au16RawValues[u8CurrentSensor] * FACTOR) / CALIBRATION_CYCLES;
		if (SM.u8CalibrationCounter == CALIBRATION_CYCLES)
		{
			SM.au16DeltaOffsets[u8CurrentSensor] = au32CalibrationBuffer[u8CurrentSensor] / FACTOR;
		}
#if DEBUG_MODE == ON
		if (u8CurrentSensor == 0)
		{
			au16FirstRawValues[SM.u8CalibrationCounter - 1] = SM.au16RawValues[u8CurrentSensor];
		}
#endif /* DEBUG_MODE */
	}

	if (SM.u8CalibrationCounter == CALIBRATION_CYCLES || u8AmountOfSensors2Calibrate == 0)
	{
		u8ReturnValue = FINISHED;
	}
	else
	{
		u8ReturnValue = IN_PROGRESS;
	}

	return u8ReturnValue;
}

static void CalculateDeltaValues(void)
{
	for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
	{
		SM.atSensorsOutput[u8SensorIndex].i16DeltaValue = (SM.au16RawValues[u8SensorIndex] - SM.au16DeltaOffsets[u8SensorIndex]) * FACTOR;
	}
}

static void FilterValuesByBuffer(void)
{
	static int16_t ai16FilterBuffer[SENSORS_AMOUNT][FILTER_BUFFER_SIZE];
	static int32_t ai32BufferSum[SENSORS_AMOUNT];
	static uint8_t u8PositionInBuffer = 0;

	for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
	{
		if (SM.tState == State_BufferFilling)
		{
			ai32BufferSum[u8SensorIndex] += SM.atSensorsOutput[u8SensorIndex].i16DeltaValue;
			ai16FilterBuffer[u8SensorIndex][u8PositionInBuffer] = SM.atSensorsOutput[u8SensorIndex].i16DeltaValue;
		}
		else
		{
			ai32BufferSum[u8SensorIndex] -= ai16FilterBuffer[u8SensorIndex][u8PositionInBuffer];
			ai32BufferSum[u8SensorIndex] += SM.atSensorsOutput[u8SensorIndex].i16DeltaValue;
			ai16FilterBuffer[u8SensorIndex][u8PositionInBuffer] = SM.atSensorsOutput[u8SensorIndex].i16DeltaValue;
			SM.atSensorsOutput[u8SensorIndex].i16FilteredValue = ai32BufferSum[u8SensorIndex] / FILTER_BUFFER_SIZE;
		}
	}
	u8PositionInBuffer++;
	if (u8PositionInBuffer == FILTER_BUFFER_SIZE)
	{
		if (SM.tState == State_BufferFilling)
		{
			SM.tState = State_Processing;
		}
		u8PositionInBuffer = 0;
	}
}

static void TakeDerivative(void)
{
	static uint8_t u8DerivativeOffset = 1;
	static int16_t LastFilteredValues[SENSORS_AMOUNT];
	for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
	{
		if (u8DerivativeOffset == 0)
		{
			SM.atSensorsOutput[u8SensorIndex].i16DerivativeValue = (SM.atSensorsOutput[u8SensorIndex].i16FilteredValue - LastFilteredValues[u8SensorIndex]);
		}
		else
		{
			u8DerivativeOffset--;
		}
		LastFilteredValues[u8SensorIndex] = SM.atSensorsOutput[u8SensorIndex].i16FilteredValue;
	}
}

static void EvaluateTouch(void)
{
	SM.u16CyclesFromLastInteraction++;
	for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
	{
		switch (SM.atSensorsTouchState[u8SensorIndex]) {
			case TouchState_FingerReleased:
				if (SM.atSensorsOutput[u8SensorIndex].i16DerivativeValue >= ABOVE_ZERO * TOUCH_DERIVATIVE_THRESHOLD)
				{
					SM.atSensorsTouchState[u8SensorIndex] = TouchState_FingerDescent;
				}
				else if (SM.atSensorsOutput[u8SensorIndex].i16FilteredValue >= TOUCH_DELTA_THRESHOLD)
				{
					SM.atSensorsOutput[u8SensorIndex].tState = SensorState_Touch;
					SM.atSensorsTouchState[u8SensorIndex] = TouchState_FingerTouch;
				}
				break;
			case TouchState_FingerDescent:
				if (SM.atSensorsOutput[u8SensorIndex].i16DerivativeValue <= ABOVE_ZERO * DERIVATIVE_ZERO_THRESHOLD)
				{
					SM.atSensorsOutput[u8SensorIndex].tState = SensorState_Touch;
					SM.atSensorsTouchState[u8SensorIndex] = TouchState_FingerTouch;
				}
				break;
			case TouchState_FingerTouch:
				SM.u16CyclesFromLastInteraction = 0;
				if (SM.atSensorsOutput[u8SensorIndex].i16DerivativeValue <= BELOW_ZERO * TOUCH_DERIVATIVE_THRESHOLD)
				{
					SM.atSensorsTouchState[u8SensorIndex] = TouchState_FingerLift;
				}
				else if (SM.atSensorsOutput[u8SensorIndex].i16FilteredValue <= IDLE_DELTA_THRESHOLD)
				{
					SM.atSensorsOutput[u8SensorIndex].tState = SensorState_Idle;
					SM.atSensorsTouchState[u8SensorIndex] = TouchState_FingerReleased;
				}
				break;
			case TouchState_FingerLift:
				if (SM.atSensorsOutput[u8SensorIndex].i16DerivativeValue >= BELOW_ZERO * DERIVATIVE_ZERO_THRESHOLD)
				{
					SM.atSensorsOutput[u8SensorIndex].tState = SensorState_Idle;
					SM.atSensorsTouchState[u8SensorIndex] = TouchState_FingerReleased;
				}
				break;
			default:
				break;
		}
	}
}

//static void UpdateCounters(void)
//{
//
//}

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
		pi16Destination[u8SensorIndex] = SM.atSensorsOutput[u8SensorIndex].i16DeltaValue;
	}
}

void SensorProcessing_ApiGetFilteredValues(int16_t *pi16Destination)
{
	for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
	{
		pi16Destination[u8SensorIndex] = SM.atSensorsOutput[u8SensorIndex].i16FilteredValue;
	}
}

void SensorProcessing_ApiGetSensorsState(SensorProcessing_SensorStates_t *ptDestination)
{
	for (uint8_t u8SensorIndex = 0; u8SensorIndex < SENSORS_AMOUNT; u8SensorIndex++)
	{
		ptDestination[u8SensorIndex] = SM.atSensorsOutput[u8SensorIndex].tState;
	}
}

//int8_t SensorProcessing_ApiGetSensorValues(int16_t *pi16Destination, uint8_t u8SensorIndex)
//{
//	//pi16Destination[0] = SM.au16RawValues[u8SensorIndex];
//	pi16Destination[0] = SM.atSensors[u8SensorIndex].i16DeltaValue;
//	pi16Destination[1] = SM.atSensorsOutput[u8SensorIndex].i16FilteredValue;
//	pi16Destination[2] = SM.atSensorsOutput[u8SensorIndex].i16DerivativeValue;
//
//	return 0;
//}

int8_t SensorProcessing_ApiGetSensorValues(SensorProcessing_SensorValues_t **ptDestination, uint8_t u8SensorIndex)
{
	*ptDestination = &SM.atSensorsOutput[u8SensorIndex];
	return 0;
}
