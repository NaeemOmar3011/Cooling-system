/*
 * LCD.h
 *
 * Created: 8/31/2023 11:30:45 AM
 *  Author: N A E E M
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "generic_macros_header.h"

#define First_Line(x) (0x80 + x)
#define Second_Line(x) (0xc0 + x)
#define Third_Line(x) (0x94 + x)
#define Forth_Line(x) (0xD4 + x)
void LCD_init(void);
void LCD_write_command(uint8_t);
void LCD_write_char(uint8_t);
void LCD_write_string(uint8_t *);
void LCD_write_num(uint16_t);



#endif /* LCD_H_ */