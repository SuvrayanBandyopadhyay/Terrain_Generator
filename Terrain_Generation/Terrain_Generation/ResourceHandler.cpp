#include"ResourceHandler.h"
#include<string>
using namespace std;

//LoadTexture("Resources/Buttons/New_Game.png"), LoadTexture("Resources/Buttons/Load_Game.png"), LoadTexture("Resources/Buttons/Settings.png"), LoadTexture("Resources/Buttons/Credits.png"), tiletex


//C:/Users/Suvra/OneDrive/Documents/Programming/C++/Steam Empires/x64/Debug/;
void ResourceHandler::load() 
{

	//Loading the textures;
	//Buttons
	newgametex = LoadTexture("Resources/Buttons/New_Game.png");
	loadgametex = LoadTexture("Resources/Buttons/Load_Game.png");
	settingstex = LoadTexture("Resources/Buttons/Settings.png");
	creditstex = LoadTexture("Resources/Buttons/Credits.png");
	
	//Tiles
	tiletex = LoadTexture("Resources/Tiles/tiles.png");


	//Settlements
	settletex = LoadTexture("Resources/Structures/Village.png");

	//Cursor
	cursortex = LoadTexture("Resources/Utilities/cursor.png");

	//Go inside button
	gointex = LoadTexture("Resources/Buttons/Go_Inside.png");

	//Next turn texture
	nextTurnTex = LoadTexture("Resources/Buttons/NextTurn.png");
}