/*
 * ioport.h
 *
 * Created: 1/9/2019 6:38:01 PM
 *  Author: chb4299
 */ 


#ifndef IOPORT_H_
#define IOPORT_H_
#include <stdint.h>
#include <avr/io.h>

#define write_port_a_data(value) write_port(&PORTA, value)
#define write_port_a_direction(value) write_port(&DDRA, value)
#define read_port_a_input() read_port(&PINA)

#define write_port_b_data(value) write_port(&PORTB, value)
#define write_port_b_direction(value) write_port(&DDRB, value)
#define read_port_b_input() read_port(&PINB)

#define write_port_c_data(value) write_port(&PORTC, value)
#define write_port_c_direction(value) write_port(&DDRC, value)
#define read_port_c_input() read_port(&PINC)

#define write_port_d_data(value) write_port(&PORTD, value)
#define write_port_d_direction(value) write_port(&DDRD, value)
#define read_port_d_input() read_port(&PIND)

#define write_port_e_data(value) write_port(&PORTE, value)
#define write_port_e_direction(value) write_port(&DDRE, value)
#define read_port_e_input() read_port(&PINE)

void write_port(volatile uint8_t* reg, uint8_t value);
uint8_t read_port(volatile uint8_t* reg);


#endif /* IOPORT_H */
