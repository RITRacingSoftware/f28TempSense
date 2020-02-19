/*
 * SN74LV4051A.h
 *
 *  Created on: Jan 30, 2020
 *      Author: Chris Blust
 */

#ifndef SN74LV4051A_H
#define SN74LV4051A_H

#include <stdint.h>

#include "ioport.h"

typedef struct
{
	bit_desc_S s0;
	bit_desc_S s1;
	bit_desc_S s2;
} sn74lv4051a_config_S;

void sn74lv4051a_select_input(sn74lv4051a_config_S* mux_config, uint8_t input);

#endif /* SN74LV4051A_H */
