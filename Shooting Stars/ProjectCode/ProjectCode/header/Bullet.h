#ifndef ARCADESHOOTER_BULLET_H
#define ARCADESHOOTER_BULLET_H

class Bullet
{
	public:
	int bulletRowPosition;
	int bulletColPosition;
	bool bulletIsAlive;
	Bullet()
	{
		bulletIsAlive = true;
	}
	Bullet(int x, int y)
	{
		bulletIsAlive = true;
		bulletRowPosition = x;
		bulletColPosition = y;
	}
	void moveDown()
	{
		if(bulletIsAlive == true)
		{
			bulletRowPosition++;
			if(bulletRowPosition == 17) {
				bulletRowPosition = 1;
				//bulletIsAlive = false;
			}
		}
		else bulletRowPosition = 1;
	}
};

#endif