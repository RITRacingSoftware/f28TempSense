/*
 * fault_status.h
 *
 *  Created on: Feb 15, 2020
 *      Author: chrisblust
 */

#ifndef FAULT_STATUS_H
#define FAULT_STATUS_H

int fault_status_get_irrational(void);
int fault_status_get_overtemp(void);

void fault_status_set_therm_overtemp(void);
void fault_status_set_therm_irrational(void);

void fault_status_clear_therm_overtemp(void);
void fault_status_clear_therm_irrational(void);

#endif /* FAULT_STATUS_H */
