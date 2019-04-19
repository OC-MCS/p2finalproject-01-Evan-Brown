#pragma once
#include <iostream>
#include <vector>
#include "game.cpp"
using namespace std;

class missile {
private:
	int missileX, missileY;

public:

	//moves the missile
	//takes missile position
	//return type: void
	void move(int missileX, int missileY)
	{
		Vector2f pos = ship.getPosition();
		missileX += 10;
		missileY += 10;
		missile.setPosition(missileX, missileY);
	}
};
