#pragma once
#include"Sprite.h"
#include"Button.h"
#include"Tile.h"
#include"Settlement.h"
#include"ResourceHandler.h"
#include"SettlementMenu.h"
#include<iostream>
#include<vector>

/*This class defines the heads up display, which displays information and buttons.
* It also contains some data which it will display

*/
class Hud 
{
private:
	Button nextTurn;//For the next turn
	Button goInside;// For accessing a settlement
	bool showInsideSettlement;//If access 
	bool hudhover;//To avoid selecting something else if we are hovering over hud

	//The settlement menu
	SettlementMenu settleMenu;
	

public:
	//Load function
	void load(ResourceHandler handler);
	//Get some booleans for other processes
	bool getHudHover();
	bool isInsideSettlement();
	//Display function
	void update(Tile* selector, std::vector<Settlement>settlements, std::map<std::string, Faction>factions, bool *isPlayerTurn, int renderWidth,int renderHeight, bool processing);
};