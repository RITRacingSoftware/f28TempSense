/*
 * task_watchdog.h
 *
 *  Created on: Mar 4, 2020
 *      Author: chrisblust
 */

#ifndef TASK_WATCHDOG_H
#define TASK_WATCHDOG_H

#define NUM_TASKS 2

typedef enum
{
	task_id_SAMPLE = 0,
	task_id_PERIODIC_1HZ = 1
} task_id_E;

void task_watchdog_init(void);

void task_watchdog_pet(task_id_E id);

int task_watchdog_tick(task_id_E id);

void task_watchdog_set_expired(task_id_E task);

task_id_E task_watchdog_get_expired_task(void);

int task_watchdog_expired(void);

#endif /* TASK_WATCHDOG_H */
