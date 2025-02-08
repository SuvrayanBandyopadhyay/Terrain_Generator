#pragma once
#include<raylib.h>
#include<iostream>
#include<vector>
#include"Button.h"
#include"Tile.h"
#include"MapGen.h"



class GameMenu 
{
protected:
	//All the buttons
	Button newgame;
	Button loadgame;
	Button settings;
	Button credits;
	//The tilemap of the loading screen
	std::vector<Tile> menutiles;
public:
	//Sets up the game menu
	void setup(Texture2D newgametex, Texture2D loadgametex, Texture2D settingstex, Texture2D creditstex, Texture2D tiletex);
	//Load the initial things

	//Runs one iteration of the menu loop and returns the next state 
	int run(Vector2 mpos);
};