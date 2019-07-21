/*
 * port.h
 *
 * Created: 1/9/2019 6:38:01 PM
 *  Author: chb4299
 */ 


#ifndef PORT_H_
#define PORT_H_
#include <stdint.h>
#include <avr/io.h>

#define write_port_a_data(value) write_port(PORTA, value)
#define write_port_a_direction(value) write_port(DDRA, value)
#define read_port_a_input() read_port(PINA)

void write_port(uint8_t* reg, uint8_t value);
uint8_t read_port(uint8_t* reg);



void writePortA(unsigned char pos, unsigned char data);

void writePortC( uint8_t pos, uint8_t val );

#endif /* PORT_H_ */
