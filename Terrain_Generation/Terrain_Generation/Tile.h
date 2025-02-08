#pragma once
#include"Sprite.h"


enum tileType {land,hill,mountain,forest,snow,snow_hill,snow_mountain,snow_forest,desert,desert_hill,desert_mountain,sea,ocean};
class Tile:public Sprite 
{
protected:
	std::vector<Rectangle> sources;
	
	
public:
	//The type
	tileType type;

	//Does a river flow through it or not
	bool river;
	//Amount of  irrigation (Farming bonus)
	float irrigated;


	Tile(Texture2D ntex, tileType t);
	Tile(char*texname,tileType t);
	//Add source(A smaller rectangle of the part which we wish to draw)
	void setSource(Rectangle rec);

	//Update the tile (Returns a cursor)
	void updateTile(Vector2 mpos,Tile** selector,bool hudhover);
	
	// Base Defence bonus for the tile
	float defence;
	//Settlement index (If no settlement then -1)
	int settlementIndex;
};

//A function to convert doubles to tiles
std::vector<Tile>createTileMap(std::vector<std::vector<double>> map, std::vector<std::vector<double>> precipitation,std::vector<std::vector<double>>snow_vec,Texture2D tiletex);
