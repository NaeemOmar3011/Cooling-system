/*
 * Timer.h
 *
 * Created: 9/5/2023 1:47:09 PM
 *  Author: C O N N E C T
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include "generic_macros_header.h"

void Timer0_Normal_noPre_init(void);
void Timer0_Normal_Pre_init(void);

void Timer0_Compare_noPre_init(uint32_t count);
void Timer0_Compare_Pre_init(uint16_t count);

void Timer1_PWM_OC1A_init(void);
void Timer1_PWM_OC1A_DC(uint8_t dc);

void Timer0_PWM_OC0_init(void);
void Timer0_PWM_OCR0_DC(uint16_t count);

void Timer1_Capture_init(void);


#endif /* TIMER_H_ */