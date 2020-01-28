/*
 * usart.c
 *
 *  Created on: Jan 25, 2020
 *      Author: chrisblust
 */

#include "ioport.h"
#include "usart.h"
#include <avr/io.h>
#include <stdio.h>

/*
 * Set the baud rate and enable the USART 1 functionalities specified.
 * @param[in] tx - 1 to enable transmitter, 0 to disable
 * @param[in] rx - 1 to enable receiver, 0 to disable
 *
 */
void usart_0_init( int tx, int rx )
{
	// Baud rate value setting
	UBRR0H = (unsigned char) (USART_BAUD_VALUE>>8);
	UBRR0L = (unsigned char) USART_BAUD_VALUE;

	// Configure for 8 bit data, no parity, and 2 stop bits
	UCSR0C = (0<<UMSEL0) | (0<<UPM0) | (0<<USBS0) | (3<<UCSZ0);

	// Enable/disable receiver and transmitter as specified
	UCSR0B = ((tx != 0)<<TXEN0) | ((rx != 0)<<RXEN0);
}

/*
 * Transmit one character using the USART 1 transmitter.
 * @param[in] data - the character to transmit
 *
 */
void usart_0_transmit(char data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)));

	/* Put data into buffer, sends the data */
	UDR0 = data;
}

#define MAX_PRINT_LENGTH 256

/*
 * Print a null terminated string out of USART0.
 * Note: Will only print MAX_PRINT_LENGTH in length
 *
 * Limited to PRINT_BUFFER_LENGTH as defined above.
 * @param[in] str - the string format
 *
 */
void usart_0_print_string(char *str)
{
	for (uint16_t i = 0; i < MAX_PRINT_LENGTH; i++)
	{
		if (str[i] != 0)
		{
			usart_0_transmit(str[i]);
		}
		else
		{
			break;
		}
	}
}

/*
 * Wait for and retrieve the next character from the receive buffer.
 * @return 8 bit data from the receive buffer.
 *
 */
char usart_0_receive()
{
	// Wait for data to be received
	while ( ! (UCSR0A & (1<<RXC0)));
	// Get and return received data from buffer
	return UDR0;
}
