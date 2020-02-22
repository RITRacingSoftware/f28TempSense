/*
 * fault_status.c
 *
 *  Created on: Feb 15, 2020
 *      Author: chrisblust
 */
#include "fault_status.h"

static int overtemp = 0;
static int irrational = 0;

int fault_status_get_overtemp(void)
{
	return overtemp;
}

int fault_status_get_irrational(void)
{
	return irrational;
}

void fault_status_set_therm_overtemp(void)
{
	overtemp = 1;
}
void fault_status_set_therm_irrational(void)
{
	irrational = 1;
}

void fault_status_clear_therm_overtemp(void)
{
	overtemp = 0;
}

void fault_status_clear_therm_irrational(void)
{
	irrational = 0;
}
