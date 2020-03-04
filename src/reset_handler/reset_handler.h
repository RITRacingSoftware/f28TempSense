/*
 * reset_handler.h
 *
 *  Created on: Mar 4, 2020
 *      Author: chrisblust
 */

#ifndef RESET_HANDLER_H
#define RESET_HANDLER_H

typedef enum
{
	reset_source_JTAG,
	reset_source_Watchdog,
	reset_source_BrownOut,
	reset_source_External,
	reset_source_PowerOn,
	reset_source_Invalid
} reset_source_E;

reset_source_E reset_handler_get_source(void);

#endif /* RESET_HANDLER_H */
