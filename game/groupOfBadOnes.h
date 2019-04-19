#pragma once
#include <iostream>
#include "alien.h"
#include "game.cpp"
using namespace std;
class groupOfBad {
public:
	//constructor that sets where the group starts
	//takes: first alien's position
	groupOfBad(int xpos, int ypos)
	{
		vector<alien> group;
		for (int i = 0; i < 10; i++)
		{
			enemy = new alien(20 + i*10, 20 + i*10);
				group.push_back(enemy);
		}
	}

	//function to move all of the aliens
	//takes: first alien's position
	//return type: void
	void move(int xpos, int ypos)
	{
		Vector2f pos = enemy.getPosition();
		xpos += 10;
		ypos += 10;
		enemy.setPosition(xpos, ypos);
	}

};
