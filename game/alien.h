#pragma once
#include <iostream>
using namespace std;

class alien {
private:
	int xpos;
	int ypos;
public:
	alien()
	{

	}

	//constructor
	//takes xpos and ypos of alien
	alien(int xpos, int ypos)
	{
		alien enemy;
		enemy.xpos = xpos;
		enemy.ypos = ypos;
	}

	//checks to see if alien is hit
	//takes position of the missile and the alien
	//return type: bool
	bool isDead(int missileX, int missileY, int xpos, int ypos)
	{
		bool dead = false;
		if (missileX == xpos && missileY == ypos)
		{
			dead = true;
		}
		return dead;
	}
};