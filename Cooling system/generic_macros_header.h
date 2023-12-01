/*
 * generic_macros_header.h
 *
 * Created: 8/12/2023 12:50:14 PM
 *  Author: safifi
 */ 


#ifndef GENERIC_MACROS_HEADER_H_
#define GENERIC_MACROS_HEADER_H_

#include <avr/io.h>   // this file include all register addresses macros like DDRA
#define F_CPU 16000000UL // set the frequency of microcontroller
#include <util/delay.h> // this header include all delay function like _delay_ms
#include <avr/interrupt.h> // this header is necessary when you deal with interrupt

#define SETBIT(REG,BIT) (REG |= 1<<BIT)
#define CLRBIT(REG,BIT) (REG &= ~(1<<BIT))
#define TOGBIT(REG,BIT) (REG ^= 1<<BIT)
#define READBIT(REG,BIT)  ((REG >> BIT) & 1)


#endif /* GENERIC_MACROS_HEADER_H_ */