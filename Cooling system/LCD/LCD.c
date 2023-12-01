/*
 * CFile1.c
 *
 * Created: 8/31/2023 11:30:10 AM
 *  Author: N A E E M
 */ 

#include "generic_macros_header.h"
#include "LCD_cfg.h"

/*****************************************************************************
* Function Name: LCD_init
* Purpose      : Init lcd in 4 bit mode, clear lcd and turn off cursor
* Parameters   : void
* Return value : void
*****************************************************************************/
void LCD_init(void){
	LCD_CFG_PINS;
	LCD_write_command(0x3); _delay_ms(4);
	LCD_write_command(0x3); _delay_ms(4);
	LCD_write_command(0x3); _delay_ms(4);
	
	LCD_write_command(0x2);
	LCD_write_command(0x28);
	LCD_write_command(0x8);
	LCD_write_command(0x1);
	LCD_write_command(0x6);
	LCD_write_command(0xC);
	_delay_ms(20);
}

/*****************************************************************************
* Function Name: LCD_write_command
* Purpose      : To make certain command
* Parameters   : uint8_t
* Return value : void
*****************************************************************************/	
void LCD_write_command(uint8_t cmd){
	RS(0);
	D4(READBIT(cmd,4));
	D5(READBIT(cmd,5));
	D6(READBIT(cmd,6));
	D7(READBIT(cmd,7));
	EN(1); _delay_ms(1); EN(0); _delay_ms(1);
	
	D4(READBIT(cmd,0));
	D5(READBIT(cmd,1));
	D6(READBIT(cmd,2));
	D7(READBIT(cmd,3));
	EN(1); _delay_ms(1); EN(0); _delay_ms(1);
	
}
/*****************************************************************************
* Function Name: LCD_write_char
* Purpose      : Write character on LCD
* Parameters   : uint8_t
* Return value : void
*****************************************************************************/
void LCD_write_char(uint8_t data){
		RS(1);
		D4(READBIT(data,4));
		D5(READBIT(data,5));
		D6(READBIT(data,6));
		D7(READBIT(data,7));
		EN(1); _delay_ms(1); EN(0); _delay_ms(1);
		
		D4(READBIT(data,0));
		D5(READBIT(data,1));
		D6(READBIT(data,2));
		D7(READBIT(data,3));
		EN(1); _delay_ms(1); EN(0); _delay_ms(1);
}
/*****************************************************************************
* Function Name: LCD_write_string
* Purpose      : Write certain string
* Parameters   : uint8_t *
* Return value : void
*****************************************************************************/
void LCD_write_string(uint8_t *str){
	uint8_t i;
	for(i=0;str[i]!='\0';i++){
	LCD_write_char(str[i]);
	}	
}
/*****************************************************************************
* Function Name: LCD_write_num
* Purpose      : Write number
* Parameters   : uint16_t
* Return value : void
*****************************************************************************/
void LCD_write_num(uint16_t num){
	int8_t i,num_rev[5];
	if(num==0) LCD_write_char(num+48);
	for(i=0;num!=0;i++){
	num_rev[i]=num%10;
	num/=10;
	}
	for(--i;i>=0;i--){
		LCD_write_char(num_rev[i]+48);
	}	
}