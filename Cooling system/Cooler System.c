/*
 * Cooling_system_control.c
 *
 * Created: 10/5/2023 11:09:18 PM
 *  Author: C O N N E C T
 */ 


#include "7-segment.h"
#include "LCD.h"
#include "Timer.h"
volatile uint16_t temp=0;

#define MAXTIMINGS	85

int dht11_dat[5] = { 0, 0, 0, 0, 0 };

uint8_t read_dht11_dat(uint8_t* temperature)
{
	uint8_t laststate	= 1;
	uint8_t counter		= 0;
	uint8_t j		= 0, i;

	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

	/* pull pin down for 18 milliseconds */
	SETBIT(DDRD,PD0);
	CLRBIT(PORTD,PD0);
	_delay_ms( 18 );
	/* then pull it up for 40 microseconds */
	SETBIT(PORTD,PD0);
	_delay_us( 40 );
	/* prepare to read the pin */
	CLRBIT(DDRD,PD0);

	/* detect change and read data */
	for ( i = 0; i < MAXTIMINGS; i++ )
	{
		counter = 0;
		while (READBIT(PIND,PD0) == laststate )
		{
			counter++;
			_delay_us( 1 );
			if ( counter == 255 )
			{
				break;
			}
		}
		laststate = READBIT(PIND,PD0);

		if ( counter == 255 )
			break;

		/* ignore first 3 transitions */
		if ( (i >= 4) && (i % 2 == 0) )
		{
			/* shove each bit into the storage bytes */
			dht11_dat[j / 8] <<= 1;
			if ( counter > 16 )
				dht11_dat[j / 8] |= 1;
			j++;
		}
	}

	/*
	 * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
	 * print it out if data is good
	 */
	if ( (j >= 40) &&
	     (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) )
	{
		*temperature = dht11_dat[2];
		return 0;
	}else  {
		return 1;
	}
}


int main(void)
{

	SETBIT(DDRA, PA7); //RED_LED
	SETBIT(DDRA, PA6); //Green_LED

	CLRBIT(PORTA, PA7); //RED_LED is off
	CLRBIT(PORTA, PA6); //Green_LED is off

	LCD_init();
	sevenS_init();
	Timer1_PWM_OC1A_init();
	Timer0_Compare_Pre_init(155);

	LCD_write_command(First_Line(0));
	LCD_write_string("TEMP: ");
	LCD_write_command(Second_Line(0));
	LCD_write_string("SPEED: ");

	while (1)
	{

		uint8_t Duty_cycle, flag = 0;
		flag=read_dht11_dat(&temp);
		if (flag == 0)
		{
			Duty_cycle = 0; // Cooler system is off

			/*LCD Display*/
			LCD_write_command(First_Line(6));
			LCD_write_num(temp);
			if (temp < 10)
			LCD_write_char(' ');
			LCD_write_string(" C");
			LCD_write_command(Second_Line(7));
			LCD_write_num(Duty_cycle);
			LCD_write_command(Second_Line(8));
			LCD_write_num(Duty_cycle);
			LCD_write_command(Second_Line(9));
			LCD_write_char(' ');

			Timer1_PWM_OC1A_DC(Duty_cycle); // DC motor output

			/*Cooler system activation*/
			while (temp >= 30)
			{
				flag=read_dht11_dat(&temp);
				if (flag == 0)
				{
					Duty_cycle = 50 + (temp - 30) * 2.5;
					if (temp >= 50)
					{
						Duty_cycle = 100;
						flag = 1;
						Timer1_PWM_OC1A_DC(98); /*DC motor output*/
						SETBIT(PORTA, PA7);   /*Red_led is ON*/
					}
					else
					{
						Timer1_PWM_OC1A_DC(Duty_cycle); /*DC motor output*/
						CLRBIT(PORTA, PA7);            /*Red_led is OFF*/
					}
				}

				/*Clear LCD when duty cycle decreases from 100*/
				if (Duty_cycle < 100 && flag == 1)
				{
					LCD_write_command(Second_Line(9));
					LCD_write_char(' ');
					flag = 0;
				}

				/*LCD Display*/
				LCD_write_command(First_Line(6));
				LCD_write_num(temp);
				LCD_write_command(Second_Line(7));
				LCD_write_num(Duty_cycle);

				SETBIT(PORTA, PA6); //Green_Led is ON
			}
			/*Cooler system is deactivated*/

			CLRBIT(PORTA, PA7); //RED_LED is OFF
			CLRBIT(PORTA, PA6); //Green_LED is OFF
		}
	}
}

/*7-Segment display*/
ISR(TIMER0_COMP_vect){
	static uint8_t flag=0;
	if(flag == 0){
		SS1_read(temp%10);
		flag=1;
	}
	else{
		SS2_read(temp/10);
		flag=0;
	}
}