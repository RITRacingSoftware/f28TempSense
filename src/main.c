#include <FreeRTOS.h>
#include <task.h>
#include "ioport/ioport.h"

#define mainLED_TASK_PRIORITY           ( tskIDLE_PRIORITY )

void led_flash_task( void *pvParameters )
{
	portTickType xLastWakeTime;
	const portTickType xFrequency = 1000;
	xLastWakeTime=xTaskGetTickCount();
	uint8_t led = 0x01;
	for( ;; )
	{
		if (led == 1)
			led = 0;
		else
			led = 1;
		write_port_a_data(led);
		vTaskDelayUntil(&xLastWakeTime,xFrequency);
	}
}

int main(int argc, char **argv) {
	write_port_a_direction(0x01);
	write_port_a_data(0x00);

	xTaskCreate(led_flash_task, ( signed char * ) "LED", configMINIMAL_STACK_SIZE, NULL, mainLED_TASK_PRIORITY, NULL);

	return 0;
}
