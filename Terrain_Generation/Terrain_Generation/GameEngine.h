#pragma once
#include<iostream>
#include<vector>
#include"Renderer.h"
#include<raylib.h>
#include<thread>
#include"GameMenu.h"
#include"ResourceHandler.h"
#include"GameHandler.h"

/*What each state represents
0 -> Menu
1 -> Start loading a new game
2 -> Load game 
3 -> Settings
4 -> Credits

5 -> Start playing the game 
*/

class GameEngine
{
private:
	//Does the drawing and camera part for us(The display part)
	Renderer GameRender;
	//Handles the menu
	//The game menu is almost self sufficient and stores and displays all resources on its own...
	GameMenu menu;
	//Handles the game
	GameHandler game;
	

	//Current state of the game
	int state;

	//The resources
	ResourceHandler resources;
	

public:
	//The initializer
	GameEngine(int render_width,int render_height);
	//Load function
	void load();
	//Run....
	void run();
	//Update the cursor
	void updateCursor(Vector2 mpos);

	//The cursor sprite
	Sprite cursor;

};

//A function to start the window
void startWindow();