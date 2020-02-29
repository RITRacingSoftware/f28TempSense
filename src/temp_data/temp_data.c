/*
 * temp_data.c
 *
 *  Created on: Feb 15, 2020
 *      Author: chrisblust
 */
#include <FreeRTOS.h>

#include <queue.h>
#include <semphr.h>
#include <portable.h>
#include "adc.h"
#include "temp_data.h"
#include "thermistor.h"
#include "multiplex.h"
#include "common_macros.h"

static double temps[NUM_THERM];

static SemaphoreHandle_t temp_data_mutex;

#define INITIAL_TEMP_DEG_C 25 // standard temp to start error free

void temp_data_init(void)
{
	// avoid errors on startup
	for (uint8_t i = 0; i < NUM_THERM; ++i)
	{
		temps[i] = INITIAL_TEMP_DEG_C;
	}

	temp_data_mutex = xSemaphoreCreateMutex();
}

void temp_data_sample_procedure(void)
{
	double deg_c = thermistor_volts_to_deg_c(adc_get_conversion_result_volts());
    temp_data_update(multiplex_get_selected(), deg_c);
}

void temp_data_update(uint8_t index, double temp)
{
	xSemaphoreTake(temp_data_mutex, portMAX_DELAY);
	index = SAT(index, 0, NUM_THERM-1);
	temps[index] = temp;
	xSemaphoreGive(temp_data_mutex);
}

double temp_data_get(uint8_t index)
{
	xSemaphoreTake(temp_data_mutex, portMAX_DELAY);
	index = SAT(index, 0, NUM_THERM-1);
	xSemaphoreGive(temp_data_mutex);
	return temps[index];
}
