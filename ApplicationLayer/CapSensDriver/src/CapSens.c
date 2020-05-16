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
		//BOTTOM_PORT->CRL = (BOTTOM_PORT->CRL & (~(BOTTOM_CONFIG_MASK))) | BOTTOM_MODE_FLOAT;
		MODIFY_REG(BOTTOM_PORT->CRL, BOTTOM_CONFIG_MASK, BOTTOM_MODE_FLOAT);
		//tConfigBottomConnection.Mode = LL_GPIO_MODE_FLOATING;
		//LL_GPIO_Init(BOTTOM_CONNECTION_PORT, &tConfigBottomConnection);
		//TOP_PORT->CRL = (TOP_PORT->CRL & (~(TOP_CONFIG_MASK))) | TOP_MODE_OUTPUT;
		MODIFY_REG(TOP_PORT->CRL, TOP_CONFIG_MASK, TOP_MODE_OUTPUT);
		//tConfigTOPConnection.Mode = LL_GPIO_MODE_OUTPUT;
		//LL_GPIO_Init(TOP_CONNECTION_PORT, &tConfigTOPConnection);
		LL_GPIO_WriteOutputPort(TOP_PORT, TOP_HIGH_LEVEL);

		NOP8;
		//LL_GPIO_WriteOutputPort(TOP_PORT, TOP_LOW_LEVEL);
		//TOP_PORT->CRL = (TOP_PORT->CRL & (~(TOP_CONFIG_MASK))) | TOP_MODE_FLOAT;
		MODIFY_REG(TOP_PORT->CRL, TOP_CONFIG_MASK, TOP_MODE_FLOAT);
		//tConfigTOPConnection.Mode = LL_GPIO_MODE_FLOATING;
		//LL_GPIO_Init(TOP_CONNECTION_PORT, &tConfigTOPConnection);

		//BOTTOM_PORT->CRL = (BOTTOM_PORT->CRL & (~(BOTTOM_CONFIG_MASK))) | BOTTOM_MODE_OUTPUT;
		MODIFY_REG(BOTTOM_PORT->CRL, BOTTOM_CONFIG_MASK, BOTTOM_MODE_OUTPUT);
		//tConfigBottomConnection.Mode = LL_GPIO_MODE_OUTPUT;
		//LL_GPIO_Init(BOTTOM_CONNECTION_PORT, &tConfigBottomConnection);
		LL_GPIO_WriteOutputPort(BOTTOM_PORT, BOTTOM_LOW_LEVEL);
		NOP8;
	}
	NOP64;
	MODIFY_REG(TOP_PORT->CRL, TOP_CONFIG_MASK, TOP_MODE_OUTPUT);
	LL_GPIO_WriteOutputPort(TOP_PORT, TOP_LOW_LEVEL);
	//LL_GPIO_WriteOutputPort(TOP_CONNECTION_PORT, TOP_CONNECTION_LOW_LEVEL);
}
