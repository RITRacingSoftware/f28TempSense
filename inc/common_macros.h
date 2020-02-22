/*
 * common_macros.h
 *
 *  Created on: Feb 1, 2020
 *      Author: chrisblust
 */

#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

#define MAX(a,b) (a < b ? b : a)
#define MIN(a,b) (a < b ? a : b)
#define SAT(input, min, max) (MAX(MIN(input,max), min))

#define BIT(pos) (1 << pos)

#endif /* COMMON_MACROS_H */
