#include "ioport.h"

#include <avr/io.h>
#include <stdint.h>

void write_port(volatile uint8_t* reg, uint8_t value)
{
	*reg = value;
}

uint8_t read_port(volatile uint8_t* reg)
{
	return *reg;
}
