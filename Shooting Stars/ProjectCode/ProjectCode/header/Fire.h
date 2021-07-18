#ifndef ARCADESHOOTER_FIRE_H
#define ARCADESHOOTER_FIRE_H

class Fire
{
	public:
	int fireRowPosition;
	int fireColPosition;
	bool fireIsAlive;
	Fire()
	{
		fireIsAlive = true;
	}
	Fire(int x, int y)
	{
		fireIsAlive = true;
		fireRowPosition = x;
		fireColPosition = y;
	}
	void setPosition(int x, int y)
	{
		fireRowPosition = x;
		fireColPosition = y;
	}
	void moveUp()
	{
		if(fireIsAlive == true)
		{
			fireRowPosition--;
			if(fireRowPosition == 0) {
				fireIsAlive = false;
			}
		}
	}
};

#endif