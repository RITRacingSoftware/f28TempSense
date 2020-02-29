/*
 * thermistor_select.c
 *
 *  Created on: Feb 1, 2020
 *      Author: Chris Blust
 */
#include <FreeRTOS.h>
#include <task.h>
#include <avr/io.h>
#include "adc.h"
#include "ioport.h"
#include "common_macros.h"
#include "sn74lv4051a.h"
#include "multiplex.h"
#include "usart.h"
#include <stdio.h>

/*
 * Definitions of the digital outputs that control the mux select pins.
 */

static sn74lv4051a_config_S configs[] =
{
	{
			{&PORTA, 5},
			{&PORTA, 4},
			{&PORTA, 3}
	},
	{
			{&PORTC, 5},
			{&PORTC, 6},
			{&PORTC, 7}
	},
	{
			{&PORTC, 0},
			{&PORTC, 1},
			{&PORTC, 2}
	}
};

static unsigned int selected_thermistor = 0;

/**
 * Set the I/O ports used for the mux into output mode.
 */
void multiplex_init(void)
{
	uint8_t a_dir = (1 << configs[0].s0.pos) | (1 << configs[0].s1.pos) | (1 << configs[0].s2.pos);
	write_port_a_direction(a_dir);

	uint8_t c_dir = (1 << configs[1].s0.pos) | (1 << configs[1].s1.pos) | (1 << configs[1].s2.pos)
			| (1 << configs[2].s0.pos) | (1 << configs[2].s1.pos) | (1 << configs[2].s2.pos);
	write_port_c_direction(c_dir);
}

void multiplex_sample_procedure(void)
{
	selected_thermistor = (selected_thermistor + 1) % NUM_THERM;

	uint8_t cluster = selected_thermistor / 8;
	multiplex_select_thermistor(cluster, selected_thermistor - (cluster * 8));
	vTaskDelay(20); // delay to let mux propagate

	uint8_t adc_channel;
	switch(cluster)
	{
		case 0:
			adc_channel = 3;
			break;
		case 1:
			adc_channel = 2;
			break;
		case 2:
			adc_channel = 1;
			break;
	}
	adc_begin_conversion(adc_channel);
}

/**
 * Select a thermistor for measurement by specifying the cluster that contains it
 * and the number resistor in the cluster.
 * @param[in] cluster [0,2] - the cluster that contains the thermistor
 * @param[in] thermistor [0,7] - the number thermister it is within the cluster
 */
void multiplex_select_thermistor(uint8_t cluster, uint8_t thermistor)
{
	cluster = SAT(cluster, 0, NUM_THERM_CLUSTER-1);
	thermistor = SAT(thermistor, 0, THERM_PER_CLUSTER-1);

	sn74lv4051a_select_input(&configs[cluster], thermistor);

	selected_thermistor = cluster * 8 + thermistor;
}

unsigned int multiplex_get_selected(void)
{
	return selected_thermistor;
}


