/*
 * sn74lv4051a.c
 *
 *  Created on: Feb 1, 2020
 *      Author: Chris Blust
 */
#include "sn74lv4051a.h"
#include "common_macros.h"

void sn74lv4051a_select_input(sn74lv4051a_config_S* mux_config, uint8_t input)
{
	input = SAT(input, 0, 7);

	*mux_config->s0.reg &= ~(1 << mux_config->s0.pos);
	*mux_config->s1.reg &= ~(1 << mux_config->s1.pos);
	*mux_config->s2.reg &= ~(1 << mux_config->s2.pos);


	if (input & (1))
		*mux_config->s0.reg |= (1 << mux_config->s0.pos);
	if (input & (1 << 1))
		*mux_config->s1.reg |= (1 << mux_config->s1.pos);
	if (input & (1 << 2))
		*mux_config->s2.reg |= (1 << mux_config->s2.pos);
}
