/*
 * _7_segment_cfg.h
 *
 * Created: 9/2/2023 9:04:34 AM
 *  Author: C O N N E C T
 */ 


#ifndef SEGMENT_CFG_H_
#define SEGMENT_CFG_H_
#include "generic_macros_header.h"
uint8_t ss[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x7,0x7f,0x6f};
/*    EN A B C D E F G 
  0--> 0 1 1 1 1 1 1 0 -->0x7E
  1--> 0 0 1 1 0 0 0 0 -->0X30
  2--> 0 1 1 0 1 1 0 1 -->0x6D
  3--> 0 1 1 1 1 0 0 1 -->0x79
  4--> 0 0 1 1 0 0 1 1 -->0x33
  5--> 0 1 0 1 1 0 1 1 -->0x5B
  6--> 0 1 0 1 1 1 1 1 -->0x5F
  7--> 0 1 1 1 0 0 0 0 -->0xE0
  8--> 0 1 1 1 1 1 1 1 -->0x7F
  9--> 0 1 1 1 1 0 1 1 -->0x7B
  
*/


#define ss_init() DDRB =0xFF; SETBIT(DDRD,PD1); 

#define SS_1(num) PORTB=0x80; PORTB|= ss[num]; \ 
		  SETBIT(PORTB,PB7);CLRBIT(PORTD,PD1);
#define SS_2(num) PORTB=0x80; PORTB|= ss[num]; \ 
		  SETBIT(PORTD,PD1);CLRBIT(PORTB,PB7);


#endif /* 7-SEGMENT_CFG_H_ */