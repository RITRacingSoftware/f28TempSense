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

#define PING_ALIVE_TASK_NAME ((signed char *) "PING_ALIVE")
#define PING_ALIVE_TASK_FREQUENCY 10000
#define PING_ALIVE_TASK_STACK_SIZE 256
#define PING_ALIVE_TASK_PRIORITY tskIDLE_PRIORITY

void ping_alive_task(void *pvParameters)
{
	portTickType xLastWakeTime;
	const portTickType xFrequency = PING_ALIVE_TASK_FREQUENCY;
	xLastWakeTime = xTaskGetTickCount();
	uint16_t iteration_count = 0;

	usart_0_init(1, 0);

	for(;;)
	{
		char str[50];
		sprintf(str, "Ping Alive: %d\n", iteration_count);
		usart_0_print_string(str);
		iteration_count++;

		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}

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

#define SAMPLE_TASK_NAME ((signed char *) "PING_ALIVE")
#define SAMPLE_TASK_FREQUENCY 1000
#define SAMPLE_TASK_STACK_SIZE 256
#define SAMPLE_TASK_PRIORITY (tskIDLE_PRIORITY + 1)

void sample_task(void *pvParameters)
{
	adc_semaphore = xSemaphoreCreateBinary();
	adc_begin_conversion(0);
	static uint8_t selected_thermistor = 0;

	for(;;)
	{
		// block until the adc ISR has fired
		xSemaphoreTake(adc_semaphore, portMAX_DELAY);

		uint16_t latest_adc_reading = adc_get_latest_conversion_result();

		char str[50];
		sprintf(str, "thermistor %d: %d\n", selected_thermistor, latest_adc_reading);
		usart_0_print_string(str);

		selected_thermistor = (selected_thermistor + 1) % NUM_THERM;
		if (selected_thermistor == 24)
		{
			selected_thermistor = 0;
		}

		uint8_t cluster = selected_thermistor / 8;
		multiplex_select_thermistor(cluster, selected_thermistor - (cluster * 8));
		vTaskDelay(100); // delay to let mux propagate

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

int main(int argc, char **argv)
{
	adc_init();
	multiplex_init();

	usart_0_init(1,0);

	//xTaskCreate(ping_alive_task, PING_ALIVE_TASK_NAME, PING_ALIVE_TASK_STACK_SIZE, NULL, PING_ALIVE_TASK_PRIORITY, NULL);
	xTaskCreate(sample_task, SAMPLE_TASK_NAME, SAMPLE_TASK_STACK_SIZE, NULL, SAMPLE_TASK_PRIORITY, NULL);

	vTaskStartScheduler();
	return 0;
}
