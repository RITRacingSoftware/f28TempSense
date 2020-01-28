/*
 * usart.h
 *
 *  Created on: Jan 25, 2020
 *      Author: Chris Blust
 */

#ifndef USART_H
#define USART_H

// Determines the correct baud rate register values for the given CPU
// speed at 9600 baud.
// According to the data sheet, 8MBd should be 51 prescale. But 57 works here for some reason.
// Play with the value if it doesn't work initially and baud rate/UART start/stop conditions agree.
#if F_CPU == 16000000UL
	#define USART_BAUD_VALUE 103
#else // Must be 8000000UL
	#define USART_BAUD_VALUE 57
#endif

void usart_0_init( int tx, int rx );

void usart_0_transmit( char data );

void usart_0_print_string(char *str);

char usart_0_receive();

#endif /* USART_H */
