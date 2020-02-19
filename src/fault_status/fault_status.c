/*
 * fault_status.c
 *
 *  Created on: Feb 15, 2020
 *      Author: chrisblust
 */
#include "fault_status.h"

static uint32_t overtemp_bit_array;
static uint32_t irrational_bit_array;

uint8_t fault_status_get_therm_overtemp(uint8_t index)
{
	return (overtemp_bit_array & (1 << index)) != 0;
}

uint8_t fault_status_get_therm_irrational(uint8_t index)
{
	return (irrational_bit_array & (1 << index)) != 0;
}

uint8_t fault_status_get_overtemp(void)
{
	return overtemp_bit_array != 0;
}

uint8_t fault_status_get_irrational(void)
{
	return irrational_bit_array != 0;
}

void fault_status_set_therm_overtemp(uint8_t index)
{
	overtemp_bit_array |= (1 << index);
}
void fault_status_set_therm_irrational(uint8_t index)
{
	irrational_bit_array |= (1 << index);
}

void fault_status_clear_therm_overtemp(uint8_t index)
{
	overtemp_bit_array &= ~(1 << index);
}

void fault_status_clear_therm_irrational(uint8_t index)
{
	irrational_bit_array &= ~(1 << index);
}
