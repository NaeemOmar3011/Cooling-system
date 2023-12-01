/*
 * LCD_cfg.h
 *
 * Created: 8/31/2023 11:31:05 AM
 *  Author: N A E E M
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_
#include "generic_macros_header.h"

#define LCD_CFG_PINS DDRC |= 0b11111100;

#define RS(x) if(x==0) CLRBIT(PORTC,PC2);else SETBIT(PORTC,PC2);
#define EN(x) if(x==0) CLRBIT(PORTC,PC3);else SETBIT(PORTC,PC3);
#define D4(x) if(x==0) CLRBIT(PORTC,PC4);else SETBIT(PORTC,PC4);
#define D5(x) if(x==0) CLRBIT(PORTC,PC5);else SETBIT(PORTC,PC5);
#define D6(x) if(x==0) CLRBIT(PORTC,PC6);else SETBIT(PORTC,PC6);
#define D7(x) if(x==0) CLRBIT(PORTC,PC7);else SETBIT(PORTC,PC7);

#endif /* LCD_CFG_H_ */