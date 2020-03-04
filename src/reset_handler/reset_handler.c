/*
 * reset_handler.c
 *
 *  Created on: Mar 4, 2020
 *      Author: chrisblust
 */
#include <avr/io.h>
#include "reset_handler.h"

#include "common_macros.h"
#include <stdio.h>
#include "usart.h"

reset_source_E reset_handler_get_source(void)
{
	int reset_source_reg = MCUSR & 0x1F;

	reset_source_E source;

	switch(reset_source_reg)
	{
		case BIT(JTRF):
			source = reset_source_JTAG;
			break;
		case BIT(WDRF):
			source = reset_source_Watchdog;
			break;
		case BIT(BORF):
			source = reset_source_BrownOut;
			break;
		case BIT(EXTRF):
			source = reset_source_External;
			break;
		case BIT(PORF):
			source = reset_source_PowerOn;
			break;
		default:
			source = reset_source_Invalid;
			break;
	}

	// clear reset source register;
	MCUSR = 0;

	return source;
}


