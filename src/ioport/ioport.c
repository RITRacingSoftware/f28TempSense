#include "../ioport/ioport.h"

#include <avr/io.h>
#include <stdint.h>

void write_port(uint8_t* reg, uint8_t value)
{
	*reg = value;
}

uint8_t read_port(uint8_t* reg)
{
	return *reg;
}
