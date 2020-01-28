#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "ioport.h"
#include "usart.h"

#define mainLED_TASK_PRIORITY           ( tskIDLE_PRIORITY )

void led_flash_task( void *pvParameters )
{
	portTickType xLastWakeTime;
	const portTickType xFrequency = 1000;
	xLastWakeTime=xTaskGetTickCount();
	uint8_t led = 0xff;
	for( ;; )
	{
		if (led == 0xff)
			led = 00;
		else
			led = 0xff;
		write_port_d_data(led);
		char str[256];
		sprintf(str, "led: %02x\n", led);
		usart_0_print_string(str);
		vTaskDelayUntil(&xLastWakeTime,xFrequency);
	}
}

int main(int argc, char **argv) {

	usart_0_init(1, 0);
	write_port_d_direction(0xff);
	write_port_d_data(0xff);

	xTaskCreate(led_flash_task, ( signed char * ) "LED", 500, NULL, mainLED_TASK_PRIORITY, NULL);

	vTaskStartScheduler();
	write_port_d_data(0xff);
	return 0;
}
