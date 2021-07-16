/*
#ifndef F_CPU
#define F_CPU 1000000UL // 16 MHz clock speed
#endif
*/
#define DIFFICULTY_LEVEL 1
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000
#include <util/delay.h>
#include <stdio.h>
#include "lcd.h" //Can be download from the bottom of this article
// we need a matrix which is 16 x 16

//row hoitese upor theke niche 1 theke 16
// but column hoitese bam theke dan e 1 theke 16
int LIFE_LEFT = 5;
int count = 0;
char life_level[10];
volatile int bulletColPosition, bulletRowPosition; //
volatile int playerRowPosition, playerColPosition; //
int enemyPosition;

struct Player {
	int playerRow, playerCol, playerLength;
}shafaet;

struct Enemy {
	int enemyRow, enemyCol, enemyLength;
}enemyistiak;

ISR(INT0_vect){	if(playerColPosition>2) playerColPosition--;	//else playerColPosition = 2;	//if(count < 11) {count ++;}}ISR(INT1_vect){	if(playerColPosition<15) playerColPosition++;	//else playerColPosition = 2;	//if(count > 0) {count --;}}

int bulletHit()
{
	if(bulletRowPosition==shafaet.playerRow)
	{
		if(bulletColPosition==shafaet.playerCol-1 || bulletColPosition==shafaet.playerCol || bulletColPosition==shafaet.playerCol+1)
		{
			return 1;
		}
		return 0;
	}
	return 0;
}

void portInit()
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0XFF;
	DDRD = 0XFF;
	shafaet.playerRow = 16;
	shafaet.playerCol = 2;
	enemyistiak.enemyRow = 1;
	enemyistiak.enemyCol = 2;
	playerRowPosition = 16;
	playerColPosition = 2;
	bulletRowPosition = 1;
}

char col_position0[] = {0b11100000, 0b01110000, 0b00111000,0b00011100,0b00001110,0b00000111,0b00000000, 0b00000000,0b00000000, 0b00000000,0b00000000,0b00000000};
char col_position1[] = {0b00000000, 0b00000000, 0b00000000,0b00000000,0b00000000,0b00000000,0b11100000, 0b01110000, 0b00111000,0b00011100,0b00001110,0b00000111};

char columns [] ={0b00000001,0b000000010, 0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000, 0b00000001,0b000000010, 0b00000100,0b00001000,0b00010000, 0b00100000,0b01000000,0b10000000};
char row_position0[] = {0b00000000, 0b00001000, 0b00010000, 0b00011000, 0b00100000, 0b00101000, 0b00110000, 0b00111000};
char row_position1[] = {0b00000001, 0b00001001, 0b00010001, 0b00011001, 0b00100001, 0b00101001, 0b00110001, 0b00111001};
char row_position2[] = {0b00000010, 0b00001010, 0b00010010, 0b00011010, 0b00100010, 0b00101010, 0b00110010, 0b00111010};
char row_position3[] = {0b00000011, 0b00001011, 0b00010011, 0b00011011, 0b00100011, 0b00101011, 0b00110011, 0b00111011};

char rowcode;
char columncode;


void showLed(int row, int column)
{
	columncode = columns[column -1];
	if (row <=8 && column <= 8)
	{
		rowcode = row_position2[row-1];
	}
	else  if (row >= 9 && column <= 8)
	{
		rowcode = row_position0[row-1-8];
	}
	else  if (row >= 9  && column >8)
	{
		rowcode = row_position1[row-1-8];
	}
	else  if ( row <=8 && column > 8)
	{
		rowcode = row_position3[row-1];
	}
	
	PORTA = columncode;
	PORTB = rowcode;
	
}

void initialize_canon(){	showLed(16,1);	_delay_ms(7);	showLed(16,2);	_delay_ms(7);	showLed(16,3);	_delay_ms(7);	showLed(15,1);	_delay_ms(7);	showLed(15,2);	_delay_ms(7);	showLed(15,3);	_delay_ms(7);	showLed(14,2);	_delay_ms(7);}


void playerMove()
{
	shafaet.playerRow = playerRowPosition;
	shafaet.playerCol = playerColPosition;
	//_delay_ms(5);
	showLed(shafaet.playerRow, shafaet.playerCol-1);
	_delay_ms(5);
	showLed(shafaet.playerRow, shafaet.playerCol);
	_delay_ms(5);
	showLed(shafaet.playerRow, shafaet.playerCol+1);
	_delay_ms(5);
	//shafaet.playerCol = (shafaet.playerCol+1)%16;
	//playerRowPosition++;
	//playerColPosition++;
}

void enemyMove(int count)
{
	enemyistiak.enemyCol = count;
	_delay_ms(50);
	showLed(enemyistiak.enemyRow, enemyistiak.enemyCol-1);
	_delay_ms(5);
	showLed(enemyistiak.enemyRow, enemyistiak.enemyCol);
	_delay_ms(5);
	showLed(enemyistiak.enemyRow, enemyistiak.enemyCol+1);
	_delay_ms(5);
	//enemyistiak.enemyCol = (enemyistiak.enemyCol+1)%16;
}

void bulletRain(){	int col;	if(bulletRowPosition ==1) {		col= rand()%17+1;		bulletColPosition = col;	}	if(bulletRowPosition!=1)	{		//col= rand()%17+1;		col = bulletColPosition ;	}	else col = bulletColPosition;		showLed(bulletRowPosition,col);	if(bulletHit()) LIFE_LEFT--;	for(int i =1; i<10; i++)	{		_delay_ms(5);		playerMove();		_delay_ms(5);	}		//_delay_ms(100);	if(bulletRowPosition==16)	{		bulletRowPosition = 1;	}	else bulletRowPosition++;}

void bulletRain2(){		int col;	col= rand()%17+1;	for(int row = 1; row <= 16; row++)	{		showLed(row,col);		_delay_ms(100);	}	}


void display(int count)
{
	if (count < 6)
	{
		PORTA = col_position0[count];
		PORTB = 0b00111001;
		_delay_ms(1000);
		//bulletRain(count);
		
		
	}
	else
	{
		PORTA = col_position1[count];
		PORTB = 0b00111000;
		_delay_ms(1000);
		//bulletRain(count);
		
		
	}
}

int main()
{
	MCUCR = MCUCR |  0b00000011;	GICR = (1 << INT1) | (1 << INT0 );	sei();
	portInit();
	Lcd4_Init();
	/*
	for (int i = 1; i<= 16; i++)
	{
		for (int j = 1; j<= 16; j++)
		
		{
			showLed(i,j);
			_delay_ms(100);
		}
		_delay_ms(10);
	}*/
	while(1)
	{
		/*
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_Char('S');
		Lcd4_Write_Char('c');
		Lcd4_Write_Char('o');
		Lcd4_Write_Char('r');
		Lcd4_Write_Char('e');
		Lcd4_Write_Char(':');
		Lcd4_Write_Char('0');
		
		Lcd4_Set_Cursor(2,1);
		Lcd4_Write_Char('L');
		Lcd4_Write_Char('i');
		Lcd4_Write_Char('v');
		Lcd4_Write_Char('e');
		Lcd4_Write_Char(':');
		Lcd4_Write_Char('5');
		*/
		
		sprintf(life_level, "%d", LIFE_LEFT);
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("Life left : ");
		Lcd4_Write_String(life_level);
		//initialize_canon();
		//playerMove();
		bulletRain();
		if(LIFE_LEFT ==0) break;
		//enemyMove(i);
		//bulletRain2();
	}
	Lcd4_Init();
	Lcd4_Set_Cursor(2,1);
	Lcd4_Write_String("Game Over");
	return 0;
}