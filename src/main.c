#include <FreeRTOS.h>
#include <task.h>
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
		{
			usart_0_write_string("slide to the left\n");
			led = 00;
		}else{
			usart_0_write_string("slide to the right\n");
			led = 0xff;}
		write_port_d_data(led);
		vTaskDelayUntil(&xLastWakeTime,xFrequency);
	}
}

int main(int argc, char **argv) {

	usart_0_init(1, 0);
	write_port_d_direction(0xff);
	write_port_d_data(0x00);

	xTaskCreate(led_flash_task, ( signed char * ) "LED", configMINIMAL_STACK_SIZE, NULL, mainLED_TASK_PRIORITY, NULL);

	vTaskStartScheduler();
	write_port_d_data(0xff);
	return 0;
}
