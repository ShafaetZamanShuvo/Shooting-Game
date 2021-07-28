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
#include "header/Bomb.h"
// we need a matrix which is 16 x 16

Player shafaet;
Fire shafaet_fire;
Bullet enemy_bullet[5];
Bomb enemy_bomb;
Enemy enemy_istiak;
Fire shafaet_fire1 = shafaet.fire1;
Fire shafaet_fire2 = shafaet.fire2;
Fire shafaet_fire3 = shafaet.fire3;
bool fire1971start = false;

void portInit();
void bulletRain();
void showLed(int x, int y);
void playerMove();
void bulletInitialize();
void showBulletLed();
void showBombLed();
int bulletHit(Bullet b, Player p);
void bulletHitCheck();
void bulletArrayMoveDown();
void fireBulletCollision(Bullet b, Player p);
void fireBulletCollisionCheck();
void fireBombCollision(Bomb *enBomb, Player *player);
void fireBombCollisionCheck();
void levelUp();
void startSequence();
void endSequence();
void bombInitialize();
int bombHit(Bomb * enBomb, Player * player);

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
	
	shafaet.initiateFire();
}

int main(void)
{
	
    MCUCR = MCUCR |  0b00000011;
    MCUCSR = MCUCSR |0b01000000;
    
    GICR = (1 << INT1) | (1 << INT0 ) | (1 << INT2);
    sei();
    portInit();
	startSequence();
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
	    if(LIFE_LEFT ==0 || LIFE_LEFT<0) break;
    }
	Lcd4_Clear();
    Lcd4_Init();
    Lcd4_Set_Cursor(1,1);
	Lcd4_Write_String("Score: ");
	Lcd4_Write_String(score_count);
	Lcd4_Set_Cursor(2,1);
    Lcd4_Write_String("Game Over!!!!");
	endSequence();
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
	for(int i =0; i<5; i++)
	{
		if(i==0) enemy_bullet[i].bulletIsAlive = true;
		else enemy_bullet[i].bulletIsAlive = false;
		enemy_bullet[i].bulletRowPosition = 1;
	}
	enemy_bomb.bombIsAlive = false;
	enemy_bomb.bombRowPosition = 1;
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
	bulletInitialize();
	
	bombInitialize();
	
	showBulletLed();
	
	if(score != 0 && score%5 == 0)
	{
		enemy_bomb.bombIsAlive = true;
	}
	

	
	showBombLed();
	
	bulletHitCheck();
	
	if(bombHit(&enemy_bomb, &shafaet)) LIFE_LEFT=LIFE_LEFT-2;
	
	
	for(int i =1; i<=10; i++)
	{
		playerMove();
		_delay_ms(6);
	}
	
	if(shafaet.fireAlive1==true) {
		showLed(shafaet.fire1.fireRowPosition, shafaet.fire1.fireColPosition);
		_delay_ms(3);
	}
	if(shafaet.fireAlive2==true) {
		showLed(shafaet.fire2.fireRowPosition, shafaet.fire2.fireColPosition);
		_delay_ms(3);
	}
	if(shafaet.fireAlive3==true) {
		showLed(shafaet.fire3.fireRowPosition, shafaet.fire3.fireColPosition);
		_delay_ms(3);
	}
	
	bulletArrayMoveDown();
	
	enemy_bomb.moveDown();

	fireBulletCollisionCheck();
	
	fireBombCollisionCheck();
	//fireBombCollisionCheck();
	
 	if(score >5 && GAME_LEVEL==0) levelUp();
	if(score >10 && GAME_LEVEL ==1) levelUp();
	
	shafaet.fireMoveUp();
	_delay_ms(10);
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

void levelUp()
{
	if(GAME_LEVEL <2) GAME_LEVEL++;
	if(GAME_LEVEL == 1)
	{
		for(int i = 1; i<3; i++)
		{
			enemy_bullet[i].bulletIsAlive = true;
		}
	}
	else if(GAME_LEVEL == 2)
	{
		for(int i = 3; i<5; i++)
		{
			enemy_bullet[i].bulletIsAlive = true;
		}
	}
}

void bombInitialize()
{
	if(enemy_bomb.bombIsAlive == true && enemy_bomb.bombRowPosition==1)
	{
		enemy_bomb.bombColPosition = rand()%17 + 1;
	}
}

void bulletInitialize()
{
	if(GAME_LEVEL == 0)
	{
		if(enemy_bullet[0].bulletRowPosition == 1)
		{
			enemy_bullet[0].bulletColPosition = rand()%17 + 1;
		}
		
	}
	else if(GAME_LEVEL == 1)
	{
		for(int i =0; i<3; i++)
		{
			if(enemy_bullet[i].bulletRowPosition == 1)
			{
				enemy_bullet[i].bulletColPosition = rand()%17 + 1;
			}
		}
	}
	else if(GAME_LEVEL == 2)
	{
		for(int i =0; i<5; i++)
		{
			if(enemy_bullet[i].bulletRowPosition == 1)
			{
				enemy_bullet[i].bulletColPosition = rand()%17 + 1;
			}
		}
	}
	if(enemy_bomb.bombRowPosition ==1)
	{
		enemy_bomb.bombColPosition = rand()%17 + 1;
	}
}

void showBombLed()
{
	if(enemy_bomb.bombIsAlive == true)
	{
		showLed(enemy_bomb.bombRowPosition, enemy_bomb.bombColPosition);
		_delay_ms(1);
		showLed(enemy_bomb.bombRowPosition+1, enemy_bomb.bombColPosition-1);
		_delay_ms(1);
		showLed(enemy_bomb.bombRowPosition+1, enemy_bomb.bombColPosition);
		_delay_ms(1);
		showLed(enemy_bomb.bombRowPosition+1, enemy_bomb.bombColPosition+1);
		_delay_ms(1);
		showLed(enemy_bomb.bombRowPosition+2, enemy_bomb.bombColPosition);
		_delay_ms(1);
	}
}

void showBulletLed()
{
	if(GAME_LEVEL == 0)
	{
		showLed(enemy_bullet[0].bulletRowPosition, enemy_bullet[0].bulletColPosition);
		_delay_ms(3);
		
	}
	else if(GAME_LEVEL == 1)
	{
		for(int i =0; i<3; i++)
		{
			showLed(enemy_bullet[i].bulletRowPosition, enemy_bullet[i].bulletColPosition);
			_delay_ms(1);
		}
	}
	else if(GAME_LEVEL == 2)
	{
		for(int i =0; i<5; i++)
		{
			showLed(enemy_bullet[i].bulletRowPosition, enemy_bullet[i].bulletColPosition);
			_delay_ms(1);
		}
	}
}



int bombHit(Bomb * enBomb, Player * player)
{
	if((*enBomb).bombRowPosition ==(*player).playerRowPosition - 4)
	{
		if((*enBomb).bombColPosition == (*player).playerColPosition)
		{
			return 1;
		}
		return 0;
	}
	else if((*enBomb).bombRowPosition==(*player).playerRowPosition -3)
	{
		if((*enBomb).bombColPosition == (*player).playerColPosition-1 || (*enBomb).bombColPosition == (*player).playerColPosition+1)
		{
			return 1;
		}
		return 0;
	}
	return 0;
}

int bulletHit(Bullet * enBullet, Player * player)
{
	if((*enBullet).bulletRowPosition==(*player).playerRowPosition - 2)
	{
		if((*enBullet).bulletColPosition == (*player).playerColPosition)
		{
			return 1;
		}
		return 0;
	}
	else if((*enBullet).bulletRowPosition==(*player).playerRowPosition -1)
	{
		if((*enBullet).bulletColPosition == (*player).playerColPosition-1 || (*enBullet).bulletColPosition == (*player).playerColPosition+1)
		{
			return 1;
		}
		return 0;
	}
	return 0;
}

void bulletHitCheck()
{
	if(GAME_LEVEL == 0)
	{
		if(bulletHit(&enemy_bullet[0], &shafaet)) LIFE_LEFT--;
	}
	else if(GAME_LEVEL == 1)
	{
		for(int i =0; i<3; i++)
		{
			if(bulletHit(&enemy_bullet[i], &shafaet)) LIFE_LEFT--;
		}
	}
	else if(GAME_LEVEL == 2)
	{
		for(int i =0; i<5; i++)
		{
			if(bulletHit(&enemy_bullet[i], &shafaet)) LIFE_LEFT--;
		}
	}
}

void bulletArrayMoveDown()
{
	if(GAME_LEVEL ==0)
	{
		enemy_bullet[0].moveDown();
	}
	else if(GAME_LEVEL == 1)
	{
		for(int i =0; i<3; i++)
		{
			enemy_bullet[i].moveDown();
		}
	}
	else if(GAME_LEVEL == 2)
	{
		for(int i =0; i<5; i++)
		{
			enemy_bullet[i].moveDown();
		}
	}
}

void fireBulletCollision(Bullet *enBullet, Player *player)
{
	if((*player).fireAlive1 == true || (*player).fireAlive2 == true ||
	(*player).fireAlive3 == true)
	{
		if(((*player).fire1.fireRowPosition-1 == (*enBullet).bulletRowPosition ||
		(*player).fire1.fireRowPosition == (*enBullet).bulletRowPosition)
		&& (*player).fire1.fireColPosition == (*enBullet).bulletColPosition)
		{
			score++;
			(*enBullet).bulletRowPosition = 1;
			(*player).fireAlive1 = false;
			(*player).fire1.fireIsAlive = false;
		}
		if(((*player).fire2.fireRowPosition-1 == (*enBullet).bulletRowPosition
		|| (*player).fire2.fireRowPosition == (*enBullet).bulletRowPosition)
		&& (*player).fire2.fireColPosition == (*enBullet).bulletColPosition)
		{
			score++;
			(*enBullet).bulletRowPosition = 1;
			(*player).fireAlive2 = false;
			(*player).fire2.fireIsAlive = false;
		}
		if(((*player).fire3.fireRowPosition-1 == (*enBullet).bulletRowPosition
		|| (*player).fire3.fireRowPosition == (*enBullet).bulletRowPosition)
		&& (*player).fire3.fireColPosition == (*enBullet).bulletColPosition)
		{
			score++;
			(*enBullet).bulletRowPosition = 1;
			(*player).fireAlive3 = false;
			(*player).fire3.fireIsAlive = false;
		}
	}
}

void fireBombCollision(Bomb *enBomb, Player *player)
{
	if((*player).fireAlive1 == true || (*player).fireAlive2 == true ||
	(*player).fireAlive3 == true)
	{
		if((((*player).fire1.fireRowPosition-1 == (*enBomb).bombRowPosition + 3 ||
		(*player).fire1.fireRowPosition == (*enBomb).bombRowPosition + 3)
		&& (*player).fire1.fireColPosition == (*enBomb).bombColPosition)
		||
		(((*player).fire1.fireRowPosition-1 == (*enBomb).bombRowPosition +3 ||
		(*player).fire1.fireRowPosition == (*enBomb).bombRowPosition + 3)
		&& (*player).fire1.fireColPosition == (*enBomb).bombColPosition+3))
		{
			score = score + 2;
			(*enBomb).bombRowPosition = 1;
			(*enBomb).bombIsAlive = false;
			(*player).fireAlive1 = false;
			(*player).fire1.fireIsAlive = false;
		}
		if((((*player).fire2.fireRowPosition-1 == (*enBomb).bombRowPosition + 3 ||
		(*player).fire2.fireRowPosition == (*enBomb).bombRowPosition + 3)
		&& (*player).fire2.fireColPosition == (*enBomb).bombColPosition)
		||
		(((*player).fire2.fireRowPosition-1 == (*enBomb).bombRowPosition +3 ||
		(*player).fire2.fireRowPosition == (*enBomb).bombRowPosition + 3)
		&& (*player).fire2.fireColPosition == (*enBomb).bombColPosition+3))
		{
			score = score + 2;
			(*enBomb).bombRowPosition = 1;
			(*enBomb).bombIsAlive = false;
			(*player).fireAlive2 = false;
			(*player).fire2.fireIsAlive = false;
		}
		if((((*player).fire3.fireRowPosition-1 == (*enBomb).bombRowPosition + 3 ||
		(*player).fire3.fireRowPosition == (*enBomb).bombRowPosition + 3)
		&& (*player).fire3.fireColPosition == (*enBomb).bombColPosition)
		||
		(((*player).fire3.fireRowPosition-1 == (*enBomb).bombRowPosition +3 ||
		(*player).fire3.fireRowPosition == (*enBomb).bombRowPosition + 3)
		&& (*player).fire3.fireColPosition == (*enBomb).bombColPosition+3))
		{
			score = score + 2;
			(*enBomb).bombRowPosition = 1;
			(*enBomb).bombIsAlive = false;
			(*player).fireAlive3 = false;
			(*player).fire3.fireIsAlive = false;
		}
	}
}

void fireBombCollisionCheck()
{
	fireBombCollision(&enemy_bomb, &shafaet);
}

void fireBulletCollisionCheck()
{
	if(GAME_LEVEL ==0)
	{
		fireBulletCollision(&enemy_bullet[0], &shafaet);
	}
	else if(GAME_LEVEL ==1)
	{
		for(int i=0; i<3; i++)
		{
			fireBulletCollision(&enemy_bullet[i], &shafaet);
		}
	}
	else if(GAME_LEVEL ==2)
	{
		for(int i=0; i<5; i++)
		{
			fireBulletCollision(&enemy_bullet[i], &shafaet);
		}
	}
}

void startSequence()
{
	//1
	
	for (int i = 0; i<10; i++)
	{
		showLed(1,8);_delay_ms(3);
		showLed(1,9);_delay_ms(3);
		showLed(2,7);_delay_ms(3);
		showLed(2,8);_delay_ms(3);
		showLed(2,9);_delay_ms(3);
		showLed(3,6);_delay_ms(3);
		showLed(3,7);_delay_ms(3);
		showLed(3,8);_delay_ms(3);
		showLed(3,9);_delay_ms(3);
		for(int i = 4; i<=14; i++)
		{
			showLed(i,8);_delay_ms(3);
			showLed(i,9);_delay_ms(3);
		}
		showLed(15,7);_delay_ms(3);
		showLed(15,8);_delay_ms(3);
		showLed(15,9);_delay_ms(3);
		showLed(15,10);_delay_ms(3);
		showLed(16,6);_delay_ms(3);
		showLed(16,7);_delay_ms(3);
		showLed(16,8);_delay_ms(3);
		showLed(16,9);_delay_ms(3);
		showLed(16,10);_delay_ms(3);
		showLed(16,11); _delay_ms(3);
	}
	
	//2
	for (int i = 0; i<10; i++)
	{
		for (int i = 4; i<= 13; i++)
		{
			showLed(3,i);_delay_ms(3);
			showLed(4,i); _delay_ms(3);
		}
		showLed(5,4);_delay_ms(3);
		showLed(5,5);_delay_ms(3);
		showLed(5,6);_delay_ms(3);
		showLed(5,12);_delay_ms(3);
		showLed(5,13);_delay_ms(3);
		showLed(6,4);_delay_ms(3);
		showLed(6,5);_delay_ms(3);
		showLed(6,6);_delay_ms(3);
		showLed(6,12);_delay_ms(3);
		showLed(6,13);_delay_ms(3);
		showLed(7,11);_delay_ms(3);
		showLed(7,12);_delay_ms(3);
		showLed(8,10);_delay_ms(3);
		showLed(8,11);_delay_ms(3);
		showLed(9,9);_delay_ms(3);
		showLed(9,10);_delay_ms(3);
		showLed(10,8);_delay_ms(3);
		showLed(10,9);_delay_ms(3);
		showLed(11,7);_delay_ms(3);
		showLed(11,8);_delay_ms(3);
		showLed(12,6);_delay_ms(3);
		showLed(12,7);_delay_ms(3);
		showLed(13,5);_delay_ms(3);
		showLed(13,6);_delay_ms(3);
		showLed(14,4);_delay_ms(3);
		showLed(14,5);_delay_ms(3);
		for (int i = 4; i<= 13; i++)
		{
			showLed(15,i);_delay_ms(3);
			showLed(16,i); _delay_ms(3);
		}
		
	}
	
	for (int i = 0; i<10; i++)
	{
		for (int i = 4; i<= 13; i++)
		{
			showLed(2,i);_delay_ms(3);
			showLed(3,i); _delay_ms(3);
		}
		showLed(4,4);_delay_ms(3);
		showLed(4,5);_delay_ms(3);
		showLed(4,6);_delay_ms(3);
		showLed(4,12);_delay_ms(3);
		showLed(4,13);_delay_ms(3);
		showLed(4,4);_delay_ms(3);
		showLed(5,5);_delay_ms(3);
		showLed(5,6);_delay_ms(3);
		showLed(5,12);_delay_ms(3);
		showLed(5,13);_delay_ms(3);
		for (int i = 6; i<=11; i++)
		{
			if (i == 8 || i == 9)
			{
				showLed(i,9);_delay_ms(3);
				showLed(i,10);_delay_ms(3);
				showLed(i,11);_delay_ms(3);
				showLed(i,12);_delay_ms(3);
				showLed(i,13);_delay_ms(3);
			}
			else
			{
				showLed(i,12);_delay_ms(3);
				showLed(i,13);_delay_ms(3);
			}
			
		}
		
		showLed(12,4);_delay_ms(3);
		showLed(13,5);_delay_ms(3);
		showLed(13,6);_delay_ms(3);
		showLed(13,12);_delay_ms(3);
		showLed(13,13);_delay_ms(3);
		showLed(14,4);_delay_ms(3);
		showLed(14,5);_delay_ms(3);
		showLed(14,6);_delay_ms(3);
		showLed(14,12);_delay_ms(3);
		showLed(14,13);_delay_ms(3);
		for (int i = 4; i<= 13; i++)
		{
			showLed(14,i);_delay_ms(3);
			showLed(15,i); _delay_ms(3);
		}
	}
}

void endSequence()
{
	for (int i =0; i<20; i++)
	{
		showLed(3,4);_delay_ms(2); showLed(3,5);_delay_ms(2); showLed(3,6);_delay_ms(2);                                             showLed(3,11);_delay_ms(2); showLed(3,12);_delay_ms(2); showLed(3,13);_delay_ms(2);
		showLed(4,4);_delay_ms(2); showLed(4,5);_delay_ms(2); showLed(4,6);_delay_ms(2);                                             showLed(4,11);_delay_ms(2); showLed(4,12);_delay_ms(2); showLed(4,13);_delay_ms(2);
		
		for (int i = 7; i<= 10; i++)
		{
			showLed(9,i);_delay_ms(2);
		}
		
		for (int i = 6; i<= 11; i++)
		{
			showLed(10,i);_delay_ms(2);
		}
		showLed(11,5);_delay_ms(2); showLed(11,6);_delay_ms(2); showLed(11,11);_delay_ms(2); showLed(11,12);_delay_ms(2);
		showLed(12,4);_delay_ms(2); showLed(12,5);_delay_ms(2); showLed(12,12);_delay_ms(2); showLed(12,13);_delay_ms(2);
		
		
		
		
		
	}
}