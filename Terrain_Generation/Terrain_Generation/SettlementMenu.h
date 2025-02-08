#pragma once
#include<iostream>
#include"Sprite.h"
#include"Faction.h"
#include"Button.h"
#include"ResourceHandler.h"

class SettlementMenu 
{
private:
	///UNITS
	//Button for recruiting
	Button recruitButton[4];

	//For displaying Recruitment screen
	Sprite recruitmentScreen;

	//The state
	int state;
public:

	void load(ResourceHandler handler);//Load the display

	void update(Settlement s, Vector2 hudpos);//Update the display

};