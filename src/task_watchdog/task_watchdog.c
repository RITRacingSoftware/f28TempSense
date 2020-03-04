/*
 * task_watchdog.c
 *
 *  Created on: Mar 4, 2020
 *      Author: chrisblust
 */
#include "task_data.h"
#include "task_watchdog.h"
#include "usart.h"

#define NUM_ALLOWED_TIMEOUTS 5

typedef struct
{
	unsigned int counter;
	unsigned int period;
	unsigned int bucket;
} task_data_S;

static task_data_S tasks[NUM_TASKS];
static task_id_E expired_task;
static int expired = 0;

void send_expired_payload(task_id_E task)
{
	if (task == task_id_SAMPLE)
	{
		usart_0_print_string("Sample task caused watchdog reset!\n");
	}
	else if (task == task_id_PERIODIC_1HZ)
	{
		usart_0_print_string("Periodic 1Hz Task caused watchdog reset!\n");
	}
}

void task_watchdog_init(void)
{
	tasks[task_id_SAMPLE].counter = 0;
	tasks[task_id_SAMPLE].period = SAMPLE_TASK_MAXIMUM_PERIOD;
	tasks[task_id_SAMPLE].bucket = NUM_ALLOWED_TIMEOUTS;

	tasks[task_id_PERIODIC_1HZ].counter = 0;
	tasks[task_id_PERIODIC_1HZ].period = PERIODIC_1HZ_TASK_PERIOD;
	tasks[task_id_PERIODIC_1HZ].bucket = NUM_ALLOWED_TIMEOUTS;
}

void task_watchdog_pet(task_id_E id)
{
	tasks[id].bucket += 2;
	if (tasks[id].bucket > NUM_ALLOWED_TIMEOUTS)
	{
		tasks[id].bucket = NUM_ALLOWED_TIMEOUTS;
	}
}

int task_watchdog_tick(task_id_E id)
{
	tasks[id].counter += 1;
	if (tasks[id].counter > tasks[id].period)
	{
		tasks[id].bucket -= 1;
		tasks[id].counter = 0;
	}

	return tasks[id].bucket <= 0;
}

void task_watchdog_set_expired(task_id_E task)
{
	expired_task = task;
	expired = 1;
	send_expired_payload(task);
}

int task_watchdog_expired(void)
{
	return expired;
}

task_id_E task_watchdog_get_expired_task(void)
{
	return expired_task;
}

