#pragma once
#include<string>
#include<iostream>
#include<vector>
#include"Sprite.h"
#include"Faction.h"

#include"Tile.h"
#include<map>

//This is the class for a settlement, which is the basic building block for any factionName
//Settlements have population, can train units and increase a factionName's influence
//An outpost has all the characteristics of a village, but cant level up. This is useful when
//one has to gain access to certain resources
enum SettlementLevel {outpost,village,town,city,metropolis};


class Settlement
{
private:
	std::string name;//Name of the settlement
	int population; // Population of the settlement
	std::string factionName;
	

public:
	Settlement();
	//Set name of the settlement
	void setName(std::string newname);

	//Get the name of the settlement
	std::string getName();

	//Set the population of the settlement
	void setPopulation(int newpop);
	
	//Get the population of the settlement
	int getPopulation();
	//Set name 
	void setFaction(std::string name);
	//Get name
	std::string getFaction();


	//Settlement Level
	SettlementLevel level;
	//The settlement sprite
	Sprite sprite;
	//The number of the tile on which it is situated 
	int tilenumber;
	//Inflence of tat settlement
	int influence;
	//Draw the factionName
	void drawSettlement(std::map<std::string, Faction>factionlist, int mapwidth, int mapheight);
	
};

void createRandomSettlement(std::vector<Settlement>* settlements, Faction factionName, std::string settlementname, int pop, std::vector<Tile> * tilemap, time_t currtime, Texture2D SettlementTex);