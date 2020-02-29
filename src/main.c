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
#include "fault_status.h"
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
//	static uint8_t selected_thermistor = 0;
	usart_0_print_string("Sample Task Start!\n");

	for(;;)
	{
		// block until the adc ISR has fired
		xSemaphoreTake(adc_semaphore, portMAX_DELAY);

		adc_sample_procedure();
		temp_data_sample_procedure();
		multiplex_sample_procedure();
	}
}

#define PERIODIC_1HZ_TASK_NAME ((signed char *) "Periodic 1Hz")
#define PERIODIC_1HZ_TASK_PERIOD 1000
#define PERIODIC_1HZ_TASK_STACK_SIZE 256
#define PERIODIC_1HZ_TASK_PRIORITY (tskIDLE_PRIORITY + 1)

void periodic_1Hz(void *pvParameters)
{
	portTickType xLastWakeTime;
	const portTickType xPeriod = PERIODIC_1HZ_TASK_PERIOD;
	xLastWakeTime = xTaskGetTickCount();

	usart_0_print_string("1Hz Task Start!\n");

	for(;;)
	{
		temp_monitor_1Hz();
		fault_status_1Hz();

		vTaskDelayUntil(&xLastWakeTime, xPeriod);
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
	xTaskCreate(periodic_1Hz, PERIODIC_1HZ_TASK_NAME, PERIODIC_1HZ_TASK_STACK_SIZE, NULL, PERIODIC_1HZ_TASK_PRIORITY, NULL);

	vTaskStartScheduler();
	return 0;
}
