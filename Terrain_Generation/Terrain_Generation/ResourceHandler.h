#pragma once
#include<raylib.h>
#include<vector>

//This class loads and stores all our resources
class ResourceHandler 
{
public:
	//Button Textures
	Texture2D newgametex;
	Texture2D loadgametex;
	Texture2D settingstex;
	Texture2D creditstex;
	//Tile Texture
	Texture2D tiletex;
	//Texture for all the settlements with populations
	Texture2D settletex;
	//Texture for the cursor
	Texture2D cursortex;
	//Go Inside button
	Texture2D gointex;
	//The next turn button
	Texture nextTurnTex;


	//Textures for the settlement Recruit menu
	Texture recruitButton;
	Texture recruitScreen;




	//The functions
	void load();

};
