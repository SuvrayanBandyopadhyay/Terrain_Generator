#pragma once
#include<raylib.h>
#include<vector>
#include<iostream>
#include"Tile.h"
#include"Settlement.h"
#include"hud.h"
#include"ResourceHandler.h"
#include<map>

//This class contains everything we need to run a game
class GameHandler 
{
private:
	
	int mapwidth;
	int mapheight;
	//The game map tiles
	std::vector<Tile>tilemap;

	//Rivers
	std::vector<std::pair<std::pair<Vector2 ,Vector2>,int>> rivers;
	//Settlements
	std::vector<Settlement>settlements;
	//All the factions
	std::map<std::string, Faction>factions;


public:
	//To check if loading has completed
	bool isloaded;
	//To check whether or not it is the player's turn
	bool playerTurn;
	//To initiate processing, processes ai at the end of every turn
	bool processing;


	//Loads the game
	void load(int size, ResourceHandler handler,time_t currtime, Camera2D* cam);
	//Runs the loading screen
	void loadingscreen();
	//Updates the selector
	void updateSelector();


	//Runs the game
	void run(Vector2 mpos,Vector2 campos, int renderWidth, int renderHeight);
	//The selected tile(while the game is running)
	Tile* selector;
	//The hud
	Hud gamehud;
	//Function to process the non player aspects of the game
	void processTurn();
};