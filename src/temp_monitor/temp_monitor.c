/*
 * temp_monitor.c
 *
 *  Created on: Feb 15, 2020
 *      Author: chrisblust
 */

#include "config.h"
#include "temp_data.h"
#include "fault_status.h"
#include "temp_monitor.h"
#include "usart.h"
#include "multiplex.h"
#include <stdint.h>
#include <stdio.h>

static double coldest_temp, hottest_temp;
static unsigned int coldest_index, hottest_index;

void temp_monitor_update(void)
{
	// don't want the static values changing while being calculated
	double new_coldest_temp = 1000;
	double new_hottest_temp = -1000;
	unsigned int new_coldest_index, new_hottest_index;

	for (uint8_t i = 0; i < NUM_THERM; i++)
	{
		double temp = temp_data_get(i);

		if (temp < new_coldest_temp)
		{
			new_coldest_temp = temp;
			new_coldest_index = i;
		}
		else if (temp > new_hottest_temp)
		{
			new_hottest_temp = temp;
			new_hottest_index = i;
		}

		if (temp > OVERTEMP_SET_DEG_C)
		{
			fault_status_set_therm_overtemp();
		}
		else if (temp < OVERTEMP_CLEAR_DEG_C)
		{
			fault_status_clear_therm_overtemp();
		}

		if (temp < IRRATIONAL_SET_DEG_C)
		{
			fault_status_set_therm_irrational();
		}
		else if (temp > IRRATIONAL_CLEAR_DEG_C)
		{
			fault_status_clear_therm_irrational();
		}
	}

	coldest_temp = new_coldest_temp;
	coldest_index = new_coldest_index;
	hottest_temp = new_hottest_temp;
	hottest_index = new_hottest_index;

	// Determine if a fault should be set

	if (config_rationality_check_enabled())
	{
		if (coldest_temp < IRRATIONAL_SET_DEG_C)
		{
			fault_status_set_therm_irrational();
		}
		else if (coldest_temp > IRRATIONAL_CLEAR_DEG_C)
		{
			fault_status_clear_therm_irrational();
		}
	}

	if (config_temp_monitoring_enabled())
	{
		if (hottest_temp > OVERTEMP_SET_DEG_C)
		{
			fault_status_set_therm_overtemp();
		}
		else if (hottest_temp < OVERTEMP_CLEAR_DEG_C)
		{
			fault_status_clear_therm_overtemp();
		}
	}


}

void temp_monitor_1Hz(void)
{
	temp_monitor_update();

	unsigned int hottest_index, coldest_index;
	double hottest_temp, coldest_temp;
	temp_monitor_hottest(&hottest_temp, &hottest_index);
	temp_monitor_coldest(&coldest_temp, &coldest_index);

	char buf[100];
	sprintf(buf, "Hottest is #%d at %lf deg C\r\nColdest is #%d at %lf deg C\r\n", hottest_index, hottest_temp, coldest_index, coldest_temp);
	usart_0_print_string(buf);
}

void temp_monitor_hottest(double* temp, unsigned int* index)
{
	*temp = hottest_temp;
	*index = hottest_index;
}

void temp_monitor_coldest(double* temp, unsigned int* index)
{
	*temp = coldest_temp;
	*index = coldest_index;
}
