/*
 * Timer.c
 *
 * Created: 9/5/2023 1:46:49 PM
 *  Author: C O N N E C T
 */ 

#include "Timer.h"

void Timer0_Normal_noPre_init(void){
		TCCR0 = 1;
		SETBIT(TIMSK,TOIE0);
		SETBIT(SREG,7);
		
}
void Timer0_Normal_Pre_init(void){
	TCCR0 = 0b101; // 1024 prescalar
	SETBIT(TIMSK,TOIE0);
	SETBIT(SREG,7);
}

void Timer0_Compare_noPre_init(uint32_t count){
	TCCR0 = 1;
	SETBIT(TCCR0,WGM01); //enable CTC
	SETBIT(TIMSK,OCIE0); //enable Compare Match
	SETBIT(SREG,7); 
	OCR0=count;
}
void Timer0_Compare_Pre_init(uint16_t count){
	TCCR0 = 0b101; // 1024 prescalar
	SETBIT(TCCR0,WGM01); //enable PWM
	SETBIT(TIMSK,OCIE0); //enable Compare Match
	SETBIT(SREG,7);
	OCR0=count;
}
void Timer1_PWM_OC1A_init(void){
	SETBIT(DDRD,PD5);
	SETBIT(TCCR1A,COM1A1);
	CLRBIT(TCCR1A,COM1A0);
	SETBIT(TCCR1A,WGM10);
	SETBIT(TCCR1A,WGM11);
	SETBIT(TCCR1B,WGM12);
	SETBIT(TCCR1B,CS10);
}
void Timer1_PWM_OC1A_DC(uint8_t dc){
	OCR1A = dc  * 10.23;
}

void Timer0_PWM_OC0_init(void){
	SETBIT(DDRB,PB3);
	TCCR0 = 1; // no prescalar
	SETBIT(TCCR0,WGM01);
	SETBIT(TCCR0,WGM00); //enable PWM
	CLRBIT(TCCR0,COM00);
	SETBIT(TCCR0,COM01);
	SETBIT(TIMSK,OCIE0); //enable Compare Match
	//SETBIT(SREG,7);
}

void Timer0_PWM_OCR0_DC(uint16_t count){
	count*=2.55;
	OCR0=count;
}

void Timer1_Capture_init(void){
	CLRBIT(DDRD,PD6); // ICP1 input
	TCCR1A=0;
	TCNT1=0;
	SETBIT(TIFR,ICF1); //clear flag
	SETBIT(TIMSK,TICIE1); //enable Capture interrupt
	SETBIT(SREG,7);
}

void Timer1_Compare_Init(uint16_t count) {
	TCCR1B |= (1 << CS12) | (1 << CS10);  // 1024 prescaler
	TCCR1B |= (1 << WGM12);  // CTC mode
	OCR1A = count;  // Set Compare Match value
	TIMSK |= (1 << OCIE1A);  // Enable Compare Match interrupt
	sei();  // Enable global interrupts
}