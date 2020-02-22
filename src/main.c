#include <FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include <portable.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../inc/projdefs.h"
#include "ioport.h"
#include "usart.h"
#include "adc.h"
#include "multiplex.h"
#include "thermistor.h"
#include "temp_data.h"
#include "temp_monitor.h"
#include "shutdown_control.h"

SemaphoreHandle_t adc_semaphore = NULL;
ISR(ADC_vect)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	// unblock the ADC task if it's blocked.
	// DONT switch to it (hence the "FromISR") since we need to finish the ISR
	xSemaphoreGiveFromISR(adc_semaphore, &xHigherPriorityTaskWoken);

	// if the ADC task task was unblocked, switch to it
	if (xHigherPriorityTaskWoken)
	{
		taskYIELD();
	}
}

#define SAMPLE_TASK_NAME ((signed char *) "SAMPLE")
#define SAMPLE_TASK_STACK_SIZE 256
#define SAMPLE_TASK_PRIORITY (tskIDLE_PRIORITY + 1)

void sample_task(void *pvParameters)
{
	adc_semaphore = xSemaphoreCreateBinary();
	adc_begin_conversion(0);
	static uint8_t selected_thermistor = 0;
	usart_0_print_string("Sample Task Start!\n");

	for(;;)
	{
		// block until the adc ISR has fired
		xSemaphoreTake(adc_semaphore, portMAX_DELAY);

		uint16_t latest_adc_reading = adc_get_latest_conversion_result();
		double volts = ((double)latest_adc_reading/((float)MAX_ADC_VALUE)) * 5.0;

		double deg_c = thermistor_volts_to_deg_c(volts);
		temp_data_update(selected_thermistor, deg_c);

//		char str[50];
//		sprintf(str, "thermistor %d: %lf volts: %lf adc: %d\n", selected_thermistor, deg_c, volts, latest_adc_reading);
//		usart_0_print_string(str);

		selected_thermistor = (selected_thermistor + 1) % NUM_THERM;
		if (selected_thermistor == 24)
		{
			selected_thermistor = 0;
		}

		uint8_t cluster = selected_thermistor / 8;
		multiplex_select_thermistor(cluster, selected_thermistor - (cluster * 8));
		vTaskDelay(20); // delay to let mux propagate

		uint8_t adc_channel;
		switch(cluster)
		{
			case 0:
				adc_channel = 3;
				break;
			case 1:
				adc_channel = 2;
				break;
			case 2:
				adc_channel = 1;
				break;
		}
		adc_begin_conversion(adc_channel);
	}
}

#define MONITOR_TASK_NAME ((signed char *) "MONITOR")
#define MONITOR_TASK_PERIOD 1000
#define MONITOR_TASK_STACK_SIZE 256
#define MONITOR_TASK_PRIORITY (tskIDLE_PRIORITY + 1)

void monitor_task(void *pvParameters)
{
	portTickType xLastWakeTime;
	const portTickType xPeriod = MONITOR_TASK_PERIOD;
	xLastWakeTime = xTaskGetTickCount();

	usart_0_print_string("Monitor Task Start!\n");

	for(;;)
	{
		temp_monitor_update();

		unsigned int hottest_index, coldest_index;
		double hottest_temp, coldest_temp;
		temp_monitor_hottest(&hottest_temp, &hottest_index);
		temp_monitor_coldest(&coldest_temp, &coldest_index);

		char buf[100];
		sprintf(buf, "Hottest is #%d at %lf deg C\nColdest is #%d at %lf deg C\n", hottest_index, hottest_temp, coldest_index, coldest_temp);
		usart_0_print_string(buf);

		vTaskDelayUntil(&xLastWakeTime, xPeriod);
		static int i = 0;
		if (i == 0)
			shutdown_control_trigger_shutdown();
		else
			shutdown_control_clear_shutdown();
		i ^= 1;
	}
}

int main(int argc, char **argv)
{
	adc_init();
	multiplex_init();
	temp_data_init();
	shutdown_control_init();

	usart_0_init(1,0);

	usart_0_print_string("Device Initialization Complete!\n");

	xTaskCreate(sample_task, SAMPLE_TASK_NAME, SAMPLE_TASK_STACK_SIZE, NULL, SAMPLE_TASK_PRIORITY, NULL);
	xTaskCreate(monitor_task, MONITOR_TASK_NAME, MONITOR_TASK_STACK_SIZE, NULL, MONITOR_TASK_PRIORITY, NULL);

	vTaskStartScheduler();
	return 0;
}
