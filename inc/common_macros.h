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

#define BIT_SET(reg, pos, val) (*((uint8_t*)reg) = (*((uint8_t*)reg) & ~(1 << pos)) | (val << pos))
#define BIT_SEL(reg, pos) ((*((uint8_t*)reg) & (1 << pos)) >> pos)

#endif /* COMMON_MACROS_H */
