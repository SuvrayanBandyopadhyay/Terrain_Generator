#pragma once
#include<iostream>
#include"Tile.h"




//The factionName class
class Faction 
{
public:
	//Name of the factionName
	std::string name;
	//Color of the factionName
	Color factionColor;

	int money;//Amount of money it has
	


	bool player_controlled;//Is this factionName controlled by the player
	
};



//Generate a random color for a new factionName
Color generateRandomColor(time_t currtime);