#ifndef ARCADESHOOTER_ENEMY_H
#define ARCADESHOOTER_ENEMY_H

class Enemy
{
	public:
	int enemyRowPosition;
	int enemyColPosition;
	bool enemyCanMove;
	Enemy()
	{
		enemyCanMove = true;
	}
	Enemy(int x, int y)
	{
		enemyRowPosition = x;
		enemyColPosition = y;
		enemyCanMove = true;
	}
	void moveLeft()
	{
		if(enemyCanMove == true)
		{
			enemyColPosition--;
			if(enemyColPosition == 1) {
				enemyCanMove = false;
			}
		}
	}
	void moveRight()
	{
		if(enemyCanMove == true)
		{
			enemyColPosition++;
			if(enemyColPosition == 16) {
				enemyCanMove = false;
			}
		}
	}
	void shootFire()
	{
		//blank now
	}
};

#endif