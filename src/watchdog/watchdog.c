/*
 * watchdog.c
 *
 *  Created on: Mar 3, 2020
 *      Author: chrisblust
 */
#include <avr/io.h>
#include <avr/wdt.h> 

#include "common_macros.h"
#include "watchdog.h"

void watchdog_init(void)
{
	// enable the watchdog
	// WDCE is "change enable" which allows WDE ("watchdog enable") to be changed
	// WDCE will revert to 0 in the next 4 clock cycles
	// WDP bits are prescaler, determine timeout. 110 is 1.1 second timeout
	//WDTCR = BIT(WDCE) | BIT(WDE);
	//WDTCR = BIT(WDE) | BIT(WDP2) | BIT(WDP1);

	wdt_enable(WDTO_1S);

	// give an initial pet
	watchdog_pet();
}

/*
 * Reset the watchdog timer.
 * We pet dogs here, we don't kick them.
 */
void watchdog_pet(void)
{
	// watchdog timer reset instruction
	//asm("WDR");
	wdt_reset();
}

