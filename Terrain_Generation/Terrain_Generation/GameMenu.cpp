#include"GameMenu.h"

using namespace std;
//Note all draw commands are wrt to 1920*1200 screen (Render size)
int a;
void GameMenu::setup(Texture2D newgametex,Texture2D loadgametex,Texture2D settingstex,Texture2D creditstex,Texture2D tiletex) 
{

	//The x offset
	int xoff = 275;
	a = newgametex.width;
	//newgame button
	newgame.loadTex(newgametex);
	newgame.setPos(xoff, 200);


	//Creating tileset
	vector<vector<double>> map;
	map = genMergeFourMap(4);
	vector<vector<double>> precipitation;
	precipitation = genMergeFourMap(4);
	vector <vector<double>>snow_vec = verticalClamp(genMergeFourMap(4),4);

	//The menu tiles
	menutiles = createTileMap(map, precipitation,snow_vec, tiletex);



}


//The run command
int GameMenu::run(Vector2 mpos) 
{
	//Get the mouse postion

	//Update the buttons
	newgame.updateButton(mpos);
	loadgame.updateButton(mpos);
	settings.updateButton(mpos);
	credits.updateButton(mpos);

	//Draw everything
	//Draw the tiles
	for (int i = 0; i < menutiles.size(); i++)
	{
		menutiles[i].draw();
	}
	//Draw gray box
	DrawRectangle(-64, -64, 800, 1200, Color{ 100,100,100,200 });
	//Draw the buttons
	if (newgame.isHover)
	{
		//Draw the tint
		newgame.draw(Color{150,150,150,255});	
		//If clicked
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) 
		{
			return 1;
		}
	}
	else 
	{	
		newgame.draw();
	}

	if (loadgame.isHover)
	{
		//Draw the tint
		loadgame.draw(Color{ 150,150,150,255 });
		//If clicked
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			return 2;
		}
	}
	else
	{
		loadgame.draw();
	}

	if (settings.isHover)
	{
		//Draw the tint
		settings.draw(Color{ 150,150,150,255 });
		//If clicked
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			return 3;
		}
	}
	else
	{
		settings.draw();
		
	}

	if (credits.isHover)
	{
		//Draw the tint
		credits.draw(Color{ 150,150,150,255 });
		//If clicked
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			return 4;
		}
	}
	else
	{
		credits.draw();
		
	}


	return 0;
}