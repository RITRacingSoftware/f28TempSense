/*
 * thermistor_select.h
 *
 *  Created on: Jan 25, 2020
 *      Author: Chris Blust
 */

#ifndef MULTIPLEX_H
#define MULTIPLEX_H

#include <stdint.h>

#define NUM_THERM_CLUSTER 3
#define THERM_PER_CLUSTER 8
#define NUM_THERM (NUM_THERM_CLUSTER * THERM_PER_CLUSTER)
void multiplex_init(void);
void multiplex_sample_procedure(void);
void multiplex_select_thermistor(uint8_t cluster, uint8_t thermistor);
unsigned int multiplex_get_selected(void);

#endif /* MULTIPLEX_H */
