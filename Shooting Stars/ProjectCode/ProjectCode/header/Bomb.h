#ifndef ARCADESHOOTER_BOMB_H
#define ARCADESHOOTER_BOMB_H

class Bomb
{
	public:
	int bombRowPosition;
	int bombColPosition;
	bool bombIsAlive;
	Bomb()
	{
		bombIsAlive = true;
	}
	Bomb(int x, int y)
	{
		bombIsAlive = true;
		bombRowPosition = x;
		bombColPosition = y;
	}
	void moveDown()
	{
		if(bombIsAlive == true)
		{
			bombRowPosition++;
			if(bombRowPosition == 15) {
				bombRowPosition = 1;
				bombIsAlive = false;
			}
		}
		else bombRowPosition = 1;
	}
};

#endif