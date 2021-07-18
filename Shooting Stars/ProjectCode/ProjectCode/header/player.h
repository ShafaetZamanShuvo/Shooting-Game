#ifndef ARCADESHOOTER_PLAYER_H
#define ARCADESHOOTER_PLAYER_H
#include "Fire.h"
class Player
{
	public:
	int playerRowPosition;
	int playerColPosition;
	bool playerCanMoveLeft;
	bool playerCanMoveRight;
	int playerLifeLeft;
	int maxFireActive;
	int activeFireNumber;
	Fire fire1, fire2, fire3;
	bool fireAlive1, fireAlive2, fireAlive3;
	Player()
	{
		playerCanMoveLeft = true;
		playerCanMoveRight = true;
		playerLifeLeft = 5;
		maxFireActive = 5;
		activeFireNumber = 0;
		fireAlive1 = fireAlive2 = fireAlive3 = false;
	}
	Player(int x, int y)
	{
		playerRowPosition = x;
		playerColPosition = y;
		playerCanMoveLeft = true;
		playerCanMoveRight = true;
		playerLifeLeft = 5;
		maxFireActive = 5;
		activeFireNumber = 0;
	}
	void moveLeft()
	{
		if(playerCanMoveLeft == true)
		{
			playerCanMoveRight = true;
			playerColPosition--;
			if(playerColPosition == 2) {
				playerCanMoveLeft = false;
			}
		}
	}
	void moveRight()
	{
		if(playerCanMoveRight == true)
		{
			playerCanMoveLeft = true;
			playerColPosition++;
			if(playerColPosition == 15) {
				playerCanMoveRight = false;
			}
		}
	}
	void shootMoveUp()
	{
		//if(activeFireNumber!=0){
			//fire[activeFireNumber-1].moveUp();
		//}
		//blank now
	}
	void initiateFire()
	{
		if(fireAlive1 == false)
		{
			fire1.setPosition(playerRowPosition-3, playerColPosition);
			fire1.fireIsAlive = true;
			fireAlive1 = true;
		}
		else if(fireAlive2 == false)
		{
			fire2.setPosition(playerRowPosition-3, playerColPosition);
			fire2.fireIsAlive = true;
			fireAlive2 = true;
		}
		else if(fireAlive3 == false)
		{
			fire3.setPosition(playerRowPosition-3, playerColPosition);
			fire3.fireIsAlive = true;
			fireAlive3 = true;
		}
	}
	
	void fireMoveUp()
	{
		if(fireAlive1 == true) fire1.moveUp();
		if(fireAlive2 == true) fire2.moveUp();
		if(fireAlive3 == true) fire3.moveUp();
		if(fire1.fireIsAlive == false) fireAlive1 = false;
		if(fire2.fireIsAlive == false) fireAlive2 = false;
		if(fire3.fireIsAlive == false) fireAlive3 = false;
	}
	/*
	int active_fire_num()
	{
		int ans = 0;
		if(fire1.fireIsAlive == false) ans++;
		if(fire2.fireIsAlive == false) ans++;
		if(fire3.fireIsAlive == false) ans++;
		return ans;
	}*/
};

#endif