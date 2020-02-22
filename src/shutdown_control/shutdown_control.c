/*
 * shutdown_control.c
 *
 *  Created on: Feb 22, 2020
 *      Author: chrisblust
 */
#include "shutdown_control.h"
#include "common_macros.h"
#include <stdint.h>
#include "ioport.h"

#define SHUTDOWN_OUTPUT_BIT_POS 1

void shutdown_control_init(void)
{
	write_port_d_direction(BIT(SHUTDOWN_OUTPUT_BIT_POS));
}

void shutdown_control_trigger_shutdown(void)
{
	uint8_t reg_val = PORTB & ~BIT(SHUTDOWN_OUTPUT_BIT_POS);
	write_port_d_data(reg_val);
}

void shutdown_control_clear_shutdown(void)
{
	write_port_d_data(BIT(SHUTDOWN_OUTPUT_BIT_POS));
}


