/*
 * thermistor.c
 *
 *  Created on: Feb 13, 2020
 *      Author: chrisblust
 */
#include "thermistor.h"
#include <stdint.h>
#include <math.h>

double thermistor_volts_to_deg_c(double voltage)
{
	// -35.83ln(voltage)+59.232

	return -35.83 * log(voltage) + 59.232;
}

