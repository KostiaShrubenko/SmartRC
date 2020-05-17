/*
 * CapSens.c
 *
 *  Created on: 15 мая 2020 г.
 *      Author: 1311985
 */

#include "CapSens.h"

static LL_GPIO_InitTypeDef tConfigTOPConnection;
static LL_GPIO_InitTypeDef tConfigBottomConnection;

void InitRoutine(void)
{
	TOP_CLK_ENABLE();
	BOTTOM_CLK_ENABLE();

	tConfigBottomConnection.Pin = BOTTOM_PINS;
	tConfigBottomConnection.Mode = LL_GPIO_MODE_OUTPUT;
	tConfigBottomConnection.Speed = LL_GPIO_SPEED_FREQ_LOW;
	tConfigBottomConnection.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	tConfigBottomConnection.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(BOTTOM_PORT, &tConfigBottomConnection);

	tConfigTOPConnection.Pin = TOP_PINS;
	tConfigTOPConnection.Mode = LL_GPIO_MODE_OUTPUT;
	tConfigTOPConnection.Speed = LL_GPIO_SPEED_FREQ_LOW;
	tConfigTOPConnection.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	tConfigTOPConnection.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(TOP_PORT, &tConfigTOPConnection);
}

void ChargeRoutine(void)
{
	for (uint16_t i = 0; i < 75; i++)
	{
		MODIFY_REG(BOTTOM_PORT->CRL, BOTTOM_CRL_MASK, BOTTOM_CRL_MODE_FLOAT);
		MODIFY_REG(BOTTOM_PORT->CRH, BOTTOM_CRH_MASK, BOTTOM_CRH_MODE_FLOAT);

		MODIFY_REG(TOP_PORT->CRL, TOP_CRL_MASK, TOP_MODE_OUTPUT);
		LL_GPIO_WriteOutputPort(TOP_PORT, TOP_HIGH_LEVEL);

		//NOP4;

		MODIFY_REG(TOP_PORT->CRL, TOP_CRL_MASK, TOP_MODE_FLOAT);

		MODIFY_REG(BOTTOM_PORT->CRL, BOTTOM_CRL_MASK, BOTTOM_CRL_MODE_OUTPUT);
		MODIFY_REG(BOTTOM_PORT->CRH, BOTTOM_CRH_MASK, BOTTOM_CRH_MODE_OUTPUT);
		LL_GPIO_WriteOutputPort(BOTTOM_PORT, BOTTOM_LOW_LEVEL);

		//NOP2;
	}
	NOP64;
	MODIFY_REG(TOP_PORT->CRL, TOP_CRL_MASK, TOP_MODE_OUTPUT);
	LL_GPIO_WriteOutputPort(TOP_PORT, TOP_LOW_LEVEL);
}
