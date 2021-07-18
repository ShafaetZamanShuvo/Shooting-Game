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
#include "header/lcd.h" //Can be download from the bottom of this article
#include "header/player.h"
#include "header/enemy.h"
#include "header/fire.h"
#include "header/bullet.h"
#include "header/constant.h"
// we need a matrix which is 16 x 16

Player shafaet;
Fire shafaet_fire;
Bullet enemy_bullet;
Enemy enemy_istiak;
Fire shafaet_fire1 = shafaet.fire1;
Fire shafaet_fire2 = shafaet.fire2;
Fire shafaet_fire3 = shafaet.fire3;
bool fire1971start = false;

void portInit();
void bulletRain();
void showLed(int x, int y);
void fireMove();
void fireBulletCollision();
int bulletHit();
void playerMove();


ISR(INT0_vect)
{
	shafaet.moveLeft();
}

ISR(INT1_vect)
{
	shafaet.moveRight();
}

ISR(INT2_vect)
{
	//Lcd4_Clear();
	//bool fireAlive1 = shafaet.fireAlive1;
	//Fire ftemp = shafaet.initiateFire();
	//int ans = shafaet.active_fire_num();
	//sprintf(flag_beche_ase, "%d", ans);
	//Lcd4_Write_String(flag_beche_ase);
	//shafaet.activeFireNumber = 100;
	shafaet.initiateFire();
}

int main(void)
{
	
    MCUCR = MCUCR |  0b00000011;
    MCUCSR = MCUCSR |0b01000000;
    
    GICR = (1 << INT1) | (1 << INT0 ) | (1 << INT2);
    sei();
    portInit();
    Lcd4_Init();
	
    while(1)
    {
	    sprintf(life_level, "%d", LIFE_LEFT);
	    sprintf(score_count,"%d", score);
	    Lcd4_Set_Cursor(1,1);
	    Lcd4_Write_String("Life: ");
	    Lcd4_Write_String(life_level);
	    Lcd4_Set_Cursor(2,1);
	    Lcd4_Write_String("Score: ");
	    Lcd4_Write_String(score_count);
	    
	    bulletRain();
	    if(LIFE_LEFT ==0) break;
    }
	Lcd4_Clear();
    Lcd4_Init();
    Lcd4_Set_Cursor(1,1);
	Lcd4_Write_String("Score: ");
	Lcd4_Write_String(score_count);
	Lcd4_Set_Cursor(2,1);
    Lcd4_Write_String("Game Over!!!!");
    return 0;
}

void portInit()
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0XFF;
	DDRD = 0XFF;
	shafaet.playerRowPosition = 16;
	shafaet.playerColPosition = 8;
	enemy_bullet.bulletRowPosition = 1;
	//bulletRowPosition = 1;
	score =0;
}

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

void bulletRain()
{
	if(enemy_bullet.bulletRowPosition ==1) {
		enemy_bullet.bulletColPosition = rand()%17+1;
	}
	showLed(enemy_bullet.bulletRowPosition, enemy_bullet.bulletColPosition);
	_delay_ms(5);
	
	if(bulletHit()) LIFE_LEFT--;
	for(int i =1; i<=10; i++)
	{
		playerMove();
		_delay_ms(7);
	}
	
	if(shafaet.fireAlive1==true) {
		showLed(shafaet.fire1.fireRowPosition, shafaet.fire1.fireColPosition);
		_delay_ms(5);
		showLed(shafaet.fire1.fireRowPosition-1, shafaet.fire1.fireColPosition);
		_delay_ms(5);
	}
	if(shafaet.fireAlive2==true) {
		showLed(shafaet.fire2.fireRowPosition, shafaet.fire2.fireColPosition);
		_delay_ms(5);
		showLed(shafaet.fire2.fireRowPosition-1, shafaet.fire2.fireColPosition);
		_delay_ms(5);
	}
	if(shafaet.fireAlive3==true) {
		showLed(shafaet.fire3.fireRowPosition, shafaet.fire3.fireColPosition);
		_delay_ms(5);
		showLed(shafaet.fire2.fireRowPosition-1, shafaet.fire2.fireColPosition);
		_delay_ms(5);
	}
	
	//_delay_ms(100);
	
	if(enemy_bullet.bulletRowPosition==16)
	{
		enemy_bullet.bulletRowPosition = 1;
	}
	else 
	{
		enemy_bullet.bulletRowPosition++;
	}
	shafaet.fireMoveUp();
	
	fireBulletCollision();
	_delay_ms(10);
}


void fireMove()
{
	//no work
}

void fireBulletCollision()
{
	if(shafaet.fireAlive1 == true)
	{
		if(shafaet.fire1.fireRowPosition == enemy_bullet.bulletRowPosition && shafaet.fire1.fireColPosition == enemy_bullet.bulletColPosition)
		{
			score++;
			enemy_bullet.bulletRowPosition = 1;
			shafaet.fireAlive1 = false;
			shafaet.fire1.fireIsAlive = false;
		}
		else if(shafaet.fire2.fireRowPosition == enemy_bullet.bulletRowPosition && shafaet.fire2.fireColPosition == enemy_bullet.bulletColPosition)
		{
			score++;
			enemy_bullet.bulletRowPosition = 1;
			shafaet.fireAlive2 = false;
			shafaet.fire2.fireIsAlive = false;
		}
		else if(shafaet.fire3.fireRowPosition == enemy_bullet.bulletRowPosition && shafaet.fire3.fireColPosition == enemy_bullet.bulletColPosition)
		{
			score++;
			enemy_bullet.bulletRowPosition = 1;
			shafaet.fireAlive3 = false;
			shafaet.fire3.fireIsAlive = false;
		}
	}
	
}

int bulletHit()
{
	if(enemy_bullet.bulletRowPosition==shafaet.playerRowPosition)
	{
		if(enemy_bullet.bulletColPosition == shafaet.playerColPosition-1 || enemy_bullet.bulletColPosition == shafaet.playerColPosition 
		|| enemy_bullet.bulletColPosition == shafaet.playerColPosition+1)
		{
			return 1;
		}
		return 0;
	}
	return 0;
}

void playerMove()
{
	showLed(shafaet.playerRowPosition-2, shafaet.playerColPosition);
	_delay_ms(2);
	showLed(shafaet.playerRowPosition-1, shafaet.playerColPosition-1);
	_delay_ms(2);
	showLed(shafaet.playerRowPosition-1, shafaet.playerColPosition);
	_delay_ms(2);
	showLed(shafaet.playerRowPosition-1, shafaet.playerColPosition+1);
	_delay_ms(2);
	showLed(shafaet.playerRowPosition, shafaet.playerColPosition-1);
	_delay_ms(2);
	showLed(shafaet.playerRowPosition, shafaet.playerColPosition);
	_delay_ms(2);
	showLed(shafaet.playerRowPosition, shafaet.playerColPosition+1);
	_delay_ms(2);
}