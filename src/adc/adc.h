/*
 * adc.h
 *
 *  Created on: Jan 25, 2020
 *      Author: Chris Blust
 */

#ifndef ADC_H
#define ADC_H

#include <stdint.h>

#define MAX_ADC_VALUE 1023

void adc_init();

void adc_begin_conversion(uint8_t channel);

uint16_t adc_get_latest_conversion_result();

#endif /* ADC_H */
