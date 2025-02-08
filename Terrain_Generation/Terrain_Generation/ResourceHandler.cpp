#include"ResourceHandler.h"
#include<string>
using namespace std;

//LoadTexture("Resources/Buttons/New_Game.png"), LoadTexture("Resources/Buttons/Load_Game.png"), LoadTexture("Resources/Buttons/Settings.png"), LoadTexture("Resources/Buttons/Credits.png"), tiletex


//C:/Users/Suvra/OneDrive/Documents/Programming/C++/Steam Empires/x64/Debug/;
void ResourceHandler::load() 
{

	//Loading the textures;
	//Buttons
	newgametex = LoadTexture("C:/Users/Suvra/OneDrive/Documents/Programming/C++/Steam Empires/x64/Debug/Resources/Buttons/New_Game.png");
	loadgametex = LoadTexture("C:/Users/Suvra/OneDrive/Documents/Programming/C++/Steam Empires/x64/Debug/Resources/Buttons/Load_Game.png");
	settingstex = LoadTexture("C:/Users/Suvra/OneDrive/Documents/Programming/C++/Steam Empires/x64/Debug/Resources/Buttons/Settings.png");
	creditstex = LoadTexture("C:/Users/Suvra/OneDrive/Documents/Programming/C++/Steam Empires/x64/Debug/Resources/Buttons/Credits.png");
	
	//Tiles
	tiletex = LoadTexture("C:/Users/Suvra/OneDrive/Documents/Programming/C++/Steam Empires/x64/Debug/Resources/Tiles/tiles.png");


	//Settlements
	settletex = LoadTexture("C:/Users/Suvra/OneDrive/Documents/Programming/C++/Steam Empires/x64/Debug/Resources/Structures/Village.png");

	//Cursor
	cursortex = LoadTexture("C:/Users/Suvra/OneDrive/Documents/Programming/C++/Steam Empires/x64/Debug/Resources/Utilities/cursor.png");

	//Go inside button
	gointex = LoadTexture("C:/Users/Suvra/OneDrive/Documents/Programming/C++/Steam Empires/x64/Debug/Resources/Buttons/Go_Inside.png");

	//Next turn texture
	nextTurnTex = LoadTexture("C:/Users/Suvra/OneDrive/Documents/Programming/C++/Steam Empires/x64/Debug/Resources/Buttons/NextTurn.png");
}