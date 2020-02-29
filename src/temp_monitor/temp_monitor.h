/*
 * temp_monitor.h
 *
 *  Created on: Feb 4, 2020
 *      Author: Chris Blust
 */

#ifndef TEMP_MONITOR_H
#define TEMP_MONITOR_H

#include <stdint.h>

#define OVERTEMP_SET_DEG_C 60.0
#define OVERTEMP_CLEAR_DEG_C 55.0

#define IRRATIONAL_SET_DEG_C 2.0
#define IRRATIONAL_CLEAR_DEG_C 5.0

void temp_monitor_1Hz(void);
uint8_t temp_monitor_get_overtemp(void);
uint8_t temp_monitor_get_irrational(void);
void temp_monitor_hottest(double* temp, unsigned int* index);
void temp_monitor_coldest(double* temp, unsigned int* index);
void temp_monitor_update(void);


#endif /* TEMP_MONITOR_H */
