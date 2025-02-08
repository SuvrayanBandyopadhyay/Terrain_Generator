#include"Settlement.h"
#include"Faction.h"
#include"Tile.h"
#include<random>
using namespace std;

Settlement::Settlement() 
{
	name = " ";
	population = 0;
	factionName = " ";
	influence = 1;
}


//Set the population of the settlement
void Settlement::setPopulation(int newpop) 
{
	population = newpop;
}

//Get the population of the settlement
int Settlement::getPopulation() 
{
	return population;
}

//Set name of the settlement
void Settlement::setName(string newname) 
{
	name = newname;
}
//Get and set factionName names
string Settlement::getFaction()
{
	return factionName;
}

//Set name of the settlements
void Settlement::setFaction(string name)
{
	factionName = name;
}


//Get the name of the settlement
string Settlement::getName() 
{
	return name;
}
//Distance between a tile and a settlement
float distance(Tile t, Settlement s) 
{
	return sqrt(pow(t.pos.x - s.sprite.pos.x, 2) + pow(t.pos.y - s.sprite.pos.y, 2));

}

//Create a new settlement for a factionName
void createRandomSettlement(std::vector<Settlement>* settlements, Faction factionName,string settlementname,int pop, std::vector<Tile>* tilemap,time_t currtime,Texture2D SettlementTex) 
{
	mt19937_64 eng(currtime);
	uniform_int_distribution<int> dis(0, (int)tilemap->size()-1);

	//Size of one tile 
	float size = 128;
	float mindist = 12;

	int index = dis(eng);

	//Checking if the new settlement is close to another one or not
	bool proximity = false;
	for (int i = 0; i < settlements->size(); i++) 
	{
		if (distance(tilemap->at(index), settlements->at(i)) < mindist*size) 
		{
			proximity = true;
		}
	}

	//To ensure no infinite loop is created due to lack of space
	int maxloop = 10000;
	int c = 0;
	
	//Choosing appropriate tile
	while (tilemap->at(index).type == sea || tilemap->at(index).type == ocean || proximity == true) 
	{
		c++;
		//If the tile is not suitable... try another tile
		index = dis(eng);

		//Checking if the new settlement is close to another one or not
		proximity = false;
		for (int i = 0; i < settlements->size(); i++)
		{
			if (distance(tilemap->at(index), settlements->at(i)) < mindist*size)
			{
				proximity = true;
			}
		}

		//Break if no suitable point can be found
		if (c > maxloop) 
		{
			break;
		}
	}

	//Now create factionName
	Settlement n;
	n.setFaction(factionName.name);


	//Set name and population
	n.setName(factionName.name);
	n.setPopulation(pop);


	//Set texture
	n.sprite.loadTex(SettlementTex);
	//Set scale
	n.sprite.setScale(0.25);
	//Set position
	n.sprite.setPos(tilemap->at(index).pos);
	n.influence = 1;

	n.setName(settlementname);

	tilemap->at(index).settlementIndex = settlements->size();//Set settlement index 

	//Push back this new settlement 
	settlements->push_back(n);


}

//Draw the settlement
void Settlement::drawSettlement(std::map<string,Faction>factionlist,int mapwidth,int mapheight)
{
	Color bordercol = factionlist[factionName].factionColor;
	float size = 128;

	//Adjustment as 0,0 is the centre of the first tile
	float adj = size / 2;

	//The first point
	Vector2 p1 = sprite.pos;
	p1.x -= influence * size + size / 2;
	p1.y -= influence * size + size / 2.0;
	//Checking for out of bounds
	if (p1.x < -adj)
	{
		p1.x = -adj;
	}
	if (p1.y < -adj) 
	{
		p1.y = -adj;
	}
	if (p1.x > mapwidth*size-adj)
	{
		p1.x = mapwidth * size-adj;
	}
	if (p1.y >mapheight*size-adj)
	{
		p1.y = mapheight*size-adj;
	}

	//The second point
	Vector2 p2 = sprite.pos;
	p2.x += influence * size + size / 2;
	p2.y -= influence * size + size / 2;
	//Checking for out of bounds
	if (p2.x < -adj)
	{
		p2.x = -adj;
	}
	if (p2.y < -adj)
	{
		p2.y = -adj;
	}
	if (p2.x > mapwidth * size - adj)
	{
		p2.x = mapwidth * size - adj;
	}
	if (p2.y > mapheight * size - adj)
	{
		p2.y = mapheight * size - adj;
	}



	//The third  point
	Vector2 p3 = sprite.pos;
	p3.x += influence * size +size / 2;
	p3.y += influence * size + size / 2;

	//Checking for out of bounds
	if (p3.x < -adj)
	{
		p3.x = -adj;
	}
	if (p3.y < -adj)
	{
		p3.y = -adj;
	}
	if (p3.x > mapwidth * size - adj)
	{
		p3.x = mapwidth * size - adj;
	}
	if (p3.y > mapheight * size - adj)
	{
		p3.y = mapheight * size - adj;
	}

	//The fourth point
	Vector2 p4 = sprite.pos;
	p4.x -= influence * size + size / 2;
	p4.y += influence * size + size / 2;

	//Checking for out of bounds
	if (p4.x < -adj)
	{
		p4.x = -adj;
	}
	if (p4.y < -adj)
	{
		p4.y = -adj;
	}
	if (p4.x > mapwidth * size - adj)
	{
		p4.x = mapwidth * size - adj;
	}
	if (p4.y > mapheight * size - adj)
	{
		p4.y = mapheight * size - adj;
	}

	//Now draw the settlement
	sprite.draw();

	//And draw the boundaries

	DrawLineEx(p1, p2, 8, bordercol);
	DrawLineEx(p2, p3, 8, bordercol);
	DrawLineEx(p3, p4, 8, bordercol);
	DrawLineEx(p4, p1, 8, bordercol);

}