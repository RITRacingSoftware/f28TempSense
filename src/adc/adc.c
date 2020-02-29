/*
 * adc_sense.c
 *
 * Created: 1/25/2020
 *  Author: Chris Blust
 */
#include <avr/io.h>
#include <avr/interrupt.h>

#include "adc.h"

#define ADC_PRESCALE 0x06
static double conversion_result_volts;

/**
 * Initialize the ADC registers and enable the ADC.
 */
void adc_init(void)
{
	uint8_t adcsra = ADCSRA;

	// Ensure interrupts are enabled on the AT90
	sei();

	// Set the reference voltage
	uint8_t admux = 0;

	// Select AVCC as the reference voltage
	admux |= (1 << REFS0);
	ADMUX = admux;

	adcsra |= (1 << ADEN); // enable all of the ADC
	adcsra |= (1 << ADIE); // enable ADC interrupts
	adcsra |= (ADC_PRESCALE & 0x3); // set the prescaler to the first 3 bits of prescale

	ADCSRA = adcsra;
}

void adc_sample_procedure(void)
{
	uint16_t latest_adc_reading = adc_get_conversion_result();
	conversion_result_volts = ((double)latest_adc_reading/((float)MAX_ADC_VALUE)) * 5.0;
}

/**
 * Begin a conversion within the ADC. The adc ISR will be run following its completion.
 * @param[in] channel - the ADC channel to convert
 */
void adc_begin_conversion(uint8_t channel)
{
	uint8_t admux = ADMUX;
	// Clear mux select bits
	admux &= (0xF8);
	// Set the mux select to the desired channel
	admux |= (channel);
	ADMUX = admux;

	// Initiate the conversion
	ADCSRA |= (1 << ADSC);
}

/**
 * Read the latest value converted by the ADC.
 *
 */
uint16_t adc_get_conversion_result(void)
{
	return ADC;
}

double adc_get_conversion_result_volts(void)
{
	return conversion_result_volts;
}
