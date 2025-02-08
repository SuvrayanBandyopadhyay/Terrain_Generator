#include<random>
#include<thread>
#include<string>
#include"GameHandler.h"
#include"ResourceHandler.h"
#include"MapGen.h"

using namespace std;





//Loading
void GameHandler::load(int size,ResourceHandler handler,time_t currtime,Camera2D *cam) 
{
	isloaded = false;
	vector<vector<double>> map = genMergeFourMap(size);
	vector<vector<double>> ppt = genMergeFourMap(size);
	vector<vector<double>>snow_vec = verticalClamp(genMergeFourMap(size),size);

	tilemap = createTileMap(map, ppt,snow_vec, handler.tiletex);

	//Setting width and height
	mapwidth = map[0].size();
	mapheight = map.size();
	//The tile size
	float tsize = 128;

	//Now to get river points
	float maxdev = 30;
	mt19937_64 eng(currtime);
	uniform_real_distribution<float>dev(-maxdev, maxdev);
	for (int i = 0; i < mapheight; i++)
	{
		for (int j = 0; j < mapwidth; j++) 
		{
			Vector2 pos = tilemap[i * mapwidth + j].pos;

			//The deviated centre for more natural rivers
			Vector2 devcent = pos;
			devcent.x += dev(eng);
			devcent.y += dev(eng);
			//The river width
			double basewidth = 10;
			double width = basewidth / pow(map[i][j],1.5);
			//To correct errors of rivers not being joint
			double err = 5+width/5;

			if (tilemap[i * mapwidth + j].river) 
			{
				
				//If the tile above it is a river sea or ocean
		
				if (i!=0 &&(tilemap[(i - 1) * mapwidth + j].river|| tilemap[(i - 1) * mapwidth + j].type ==sea|| tilemap[(i - 1) * mapwidth + j].type == ocean))
				{
					
					//The points
					Vector2 a = pos;
					a.y -= tsize/2+err;
					//a.x += err;

					Vector2 b = devcent;
					b.y += err;
					

					//Adding the river
					rivers.push_back(std::pair<std::pair<Vector2, Vector2>, int>(std::pair<Vector2, Vector2>(a,b),width));

				}

				//If the tile below it is a river
	
				if ((i!= mapheight-1)&&(tilemap[(i + 1) * mapwidth + j].river || tilemap[(i + 1) * mapwidth + j].type == sea || tilemap[(i + 1) * mapwidth + j].type == ocean))
				{
					
					//The points
					Vector2 a = pos;
					a.y += tsize/2+err;
					
					
				
					Vector2 b = devcent;
					b.y -= err;
					//A little nudge

					//Adding the river
					rivers.push_back(std::pair<std::pair<Vector2, Vector2>, int>(std::pair<Vector2, Vector2>(a, b), width));

				}

				//If the tile to the left of it is a river
	
				if ((j!=0)&&(tilemap[(i) * mapwidth + (j-1)].river || tilemap[i* mapwidth + (j-1)].type == sea || tilemap[i * mapwidth + (j - 1)].type == ocean))
				{
					
					//The points
					Vector2 a = pos;
					a.x -= tsize/2+err;


					Vector2 b = devcent;
					b.x += err;
					//Adding the river
					rivers.push_back(std::pair<std::pair<Vector2, Vector2>, int>(std::pair<Vector2, Vector2>(a, b), width));

				}

				//If the tile to the right of it is a river
			
				if ((j!=mapwidth-1)&&(tilemap[(i)*mapwidth + (j + 1)].river || tilemap[(i) * mapwidth + (j+1)].type == sea || tilemap[(i) * mapwidth + (j+1)].type == ocean))
				{
					
					//The points
					Vector2 a = pos;
					a.x += tsize/2+err;
					Vector2 b = devcent;
					b.x -= err;
					//Adding the river
					rivers.push_back(std::pair<std::pair<Vector2, Vector2>, int>(std::pair<Vector2, Vector2>(a, b), width));

				}
			}
		}
	}
	

	
	//Set selected to nullptr
	selector = nullptr;


	//Loading the hud
	gamehud.load(handler);


	 
	//create settlements
	for (int i = 0; i < 10; i++) 
	{

		Faction fac;

		fac.factionColor = generateRandomColor(currtime+i);
		fac.name = "Faction " + to_string(i);
		createRandomSettlement(&settlements, fac, "Village", 100, &tilemap, currtime, handler.settletex);

		if (i == 0) 
		{
			fac.player_controlled = 1;
		}
		else
		{
			fac.player_controlled = 0;
		}

		factions.insert(std::pair<string,Faction>(fac.name,fac));//Store the factionName
	}

	cam->target = settlements[0].sprite.pos;

	//Set player turn to true
	playerTurn = 1;
	
	//Finished loading
	isloaded = true;
	processing = false;
	
	
}
//Loading screen

void GameHandler::loadingscreen() 
{
	DrawText("LOADING...", 750, 460, 100, BLACK);

}
//A function to update the selector(Basically a pointer which points to the selected tile)
void GameHandler::updateSelector()
{
	//If selector points to this
	if (selector != nullptr)
	{
		//Now to draw a box to mark the selected tile
		Vector2 pos = selector->pos;
		int size = 128;
		float thickness = 5;
		Color selectColor = RED;
		//Upper line
		//We add/subtract line thickness to avoid overlapping
		Vector2 p1 = Vector2{ pos.x - size / 2,pos.y - size / 2 };
		Vector2 p2 = Vector2{ pos.x  + size / 2,pos.y - size / 2 };
		Vector2 p3 = Vector2{ pos.x + size / 2,pos.y+ size / 2 };
		Vector2 p4 = Vector2{ pos.x - size / 2,pos.y + size / 2 };

		//Now drawing the boundaries
		DrawLineEx(p1, p2, thickness, selectColor);
		DrawLineEx(p2, p3, thickness, selectColor);
		DrawLineEx(p3, p4, thickness, selectColor);
		DrawLineEx(p4, p1, thickness, selectColor);
	}
	if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) 
	{
		selector = (Tile*)nullptr;
	}
}


void GameHandler::run(Vector2 mpos,Vector2 campos,int renderWidth,int renderHeight)
{

	//Draw all the tiles
	for (int i = 0; i < tilemap.size(); i++)
	{
		tilemap[i].updateTile(mpos,&selector,gamehud.getHudHover());
	}
	
	
	//Then draw all rivers
	for (int i = 0; i < rivers.size(); i++)
	{
		//Draw rivers
		DrawLineBezier(rivers[i].first.first, rivers[i].first.second, rivers[i].second, Color{6,160,253,234});
		
	}

	//Draw all settlements
	for (int i = 0; i < settlements.size(); i++) 
	{
		settlements[i].drawSettlement(factions, mapwidth, mapheight);
	}

	//If not inside settlement
	if (!gamehud.isInsideSettlement())
	{
		updateSelector();
	}

	//Disable camera
	EndMode2D(); 
	gamehud.update(selector,settlements,factions,&playerTurn,renderWidth,renderHeight,processing);
	//If next turn and processing has not been initiated
	if (playerTurn == false && processing == false) 
	{
		processing = true;
		thread t(&GameHandler::processTurn,this);
		t.detach();
	}

	
}

//Processing the turn
void GameHandler::processTurn() 
{
	//Creating an iterator
	map<string, Faction>::iterator iter = factions.begin();
	
	while (iter != factions.end()) 
	{
		cout << iter->first << endl;
		WaitTime(1);
		iter++;
	}

	playerTurn = true;
	processing = false;


}
