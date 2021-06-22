#ifndef F_CPU
#define F_CPU 1000000UL // 16 MHz clock speed
#endif
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "lcd.h" //Can be download from the bottom of this article
volatile int flag = 0;

ISR(INT0_vect)
{
	if(flag == 0) {flag = 1;}
	else if(flag == 1) {flag = 0;}
}

void display(int flag)
{
	
	//row_num = temp;
	if(flag == 1)
	{
		PORTA = 0b11110000;
		PORTB = 0b00111001;
		_delay_ms(1000);
		
	}
	else if(flag == 0)
	{
		PORTA = 0b01111000;
		PORTB = 0b00111001;
		_delay_ms(1000);
	}
	
}

int main(void)
{
	
	DDRD |= 0xF0;
	DDRC = 0xFF;
	DDRB =0b11111111;
	DDRA =0b11111111;
	Lcd4_Init();
	

	
	while(1)
	{
		
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_Char('V');
		Lcd4_Write_Char('o');
		Lcd4_Write_Char('l');
		Lcd4_Write_Char('t');
		Lcd4_Write_Char('a');
		Lcd4_Write_Char('g');
		Lcd4_Write_Char('e');
		Lcd4_Write_Char(':');
		
		_delay_ms(200);
		
		MCUCR = MCUCR |  0b00000011;
		GICR = (1 << INT0);
		sei();
		
		
		if(PINB7)
		{
			
		}	
		else
		{
			
			PORTA = 0b11110000;
			PORTB = 0b00111001;
			_delay_ms(1000);
		}	
		
		display(flag);
				
		
	}
}
