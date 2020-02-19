/*
 * fault_status.h
 *
 *  Created on: Feb 15, 2020
 *      Author: chrisblust
 */

#ifndef FAULT_STATUS_H
#define FAULT_STATUS_H

#include <stdint.h>

uint8_t fault_status_get_therm_overtemp(uint8_t index);
uint8_t fault_status_get_therm_irrational(uint8_t index);

uint8_t fault_status_get_irrational(void);
uint8_t fault_status_get_overtemp(void);

void fault_status_set_therm_overtemp(uint8_t index);
void fault_status_set_therm_irrational(uint8_t index);

void fault_status_clear_therm_overtemp(uint8_t index);
void fault_status_clear_therm_irrational(uint8_t index);

#endif /* FAULT_STATUS_H */
