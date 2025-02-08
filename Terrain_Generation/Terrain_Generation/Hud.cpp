#include"Hud.h"
#include<string>
#include<raylib.h>
#include"ResourceHandler.h"


using namespace std;
//A rounding off function
float roundoff(float a, float places) 
{
	float n = pow(10.0, places);
	return round(a * n) / n;
	
}

void Hud::load(ResourceHandler handler) 
{
	goInside.loadTex(handler.gointex);
	goInside.pos = Vector2{ 1800,650 };
	goInside.setScale(0.75);

	nextTurn.loadTex(handler.nextTurnTex);
	nextTurn.setScale(0.75);
	nextTurn.pos = Vector2{ 1850,1030 };


	showInsideSettlement = false;//By default dont show inside the settlement
}
bool Hud::isInsideSettlement() 
{
	return showInsideSettlement;
}

//Processing checks if other factions are playing their turns
void Hud::update(Tile* selector, std::vector<Settlement>settlements, std::map<string, Faction>factions,bool *isPlayerTurn, int renderWidth, int renderHeight,bool processing)
{
	hudhover = false;
	float upper_right_x = 1400;
	float upper_right_y = 0;
	//Special co-ordinates for the hud without camera effect
	//Mouse x position
	float mx = ((GetMousePosition().x) / ((float)GetScreenWidth())) * (float)renderWidth;
	//Mouse y position
	float my = ((GetMousePosition().y) / ((float)GetScreenHeight())) * (float)renderHeight;

	Vector2 mpos{ mx,my };
	
	
	//We draw a rectangle in the upper right corner to give more data about the terrain
	//If the selector is not a null pointer
	
	//Since this thing moves with the camera, everything is with respect to the camera position
	if (selector != (Tile*)nullptr)
	{


		//If we access the outside of the settlement


		

		
		//If we are inside a settlement and no next turn 
		if(showInsideSettlement&&processing == false)
		{
	
			hudhover = true;//To prevent clicking affecting something else

			settleMenu.update(settlements[selector->settlementIndex],mpos);

			if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) 
			{
				showInsideSettlement = false
					;
			}

		}
		else
		{
			cout << "out" << endl;
			//Draw a rectangle in the upper right corner
			DrawRectangle(upper_right_x, upper_right_y, 2000 - upper_right_x, 600, Color{ 100,100,100,200 });
			//Create the upper right tile data
			string tile_data = "";


#pragma region Set title of tile
			//A large group of if statements
			if (selector->type == land)
			{
				tile_data += "Plains\n";
			}
			if (selector->type == hill)
			{
				tile_data += "Hills\n";
			}
			if (selector->type == mountain)
			{
				tile_data += "Temperate Mountains\n";
			}
			if (selector->type == forest)
			{
				tile_data += "Forest\n";
			}
			if (selector->type == snow)
			{
				tile_data += "Snowy Plains\n";
			}
			if (selector->type == snow_hill)
			{
				tile_data += "Cold Hills\n";
			}
			if (selector->type == snow_mountain)
			{
				tile_data += "Frigid Mountains\n";
			}
			if (selector->type == snow_forest)
			{
				tile_data += "Snowy Forests\n";
			}
			if (selector->type == desert)
			{
				tile_data += "Desert\n";
			}
			if (selector->type == desert_hill)
			{
				tile_data += "Desert Hills\n";
			}
			if (selector->type == desert_mountain)
			{
				tile_data += "Desert Mountains\n";
			}
			if (selector->type == sea)
			{
				tile_data += "Sea\n";
			}
			if (selector->type == ocean)
			{
				tile_data += "Ocean\n";
			}



#pragma endregion
			//Padding
			tile_data += "\n\n";
			//Irrigation data
			tile_data += "Irrigation: " + to_string((int)(selector->irrigated * 100.0)) + "%\n\n\n";
			//Defence data
			tile_data += "Defence: " + to_string((int)(selector->defence * 100.0)) + "%\n\n\n";
			//Settlement data(If exists)

			if (selector->settlementIndex != -1)
			{


				tile_data += "\n\n";

				tile_data += "Settlement Details: \n\n\n";


				//Add name
				try
				{


					tile_data += "Name: " + settlements[selector->settlementIndex].getName() + "\n\n\n";



					//Add population

					tile_data += "Population: " + to_string(settlements[selector->settlementIndex].getPopulation()) + "\n\n\n";
					//Faction

					tile_data += "Faction: " + settlements[selector->settlementIndex].getFaction() + "\n\n\n";
				}
				catch (exception& e)
				{


					cout << e.what() << endl;
				}


				//If player controlled and it is the player's turn


				if (*isPlayerTurn && factions[settlements[selector->settlementIndex].getFaction()].player_controlled)
				{
					goInside.updateButton(mpos);

					//If hovering
					if (!goInside.isHover)
					{
						goInside.draw();
					}
					else
					{
						hudhover = true;
						goInside.draw(DARKGRAY);
					}
					//If clicked
					if (goInside.isClicked)
					{
						showInsideSettlement = true;
					}
				}
			}
			//Display the text
			DrawText(tile_data.c_str(), upper_right_x + 32, upper_right_y + 32, 32, WHITE);





		}

		//If processing is true, come out of settlement
		if (processing == true) 
		{
			showInsideSettlement = false;
		}

	}
	

	//NEXT TURN LOGIC
    
	//If hovering and player turn

	if (*isPlayerTurn)
	{
		nextTurn.updateButton(mpos);

		if (nextTurn.isHover)
		{
			hudhover = true;
			nextTurn.draw(DARKGRAY);
		}
		//Else
		else
		{
			nextTurn.draw();
		}
		//If clicked
		if (nextTurn.isClicked)
		{
			*isPlayerTurn = false;
		}
	}
	
	//Draw with a dark highlight to signify it cant be clicked again
	else 
	{
		nextTurn.draw(GRAY);
	}
}

//To get hud hover
bool Hud::getHudHover() 
{
	return hudhover;
}