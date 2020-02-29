/*
 * temp_data.h
 *
 *  Created on: Feb 15, 2020
 *      Author: chrisblust
 */

#ifndef TEMP_DATA_H
#define TEMP_DATA_H

#include <stdint.h>

void temp_data_init(void);
void temp_data_sample_procedure(void);
void temp_data_update(uint8_t index, double temp);
double temp_data_get(uint8_t index);

#endif /* TEMP_DATA_H */
