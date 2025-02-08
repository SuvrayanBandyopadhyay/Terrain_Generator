#include"Faction.h"
#include<random>
#include<vector>
#include"Tile.h"



using namespace std;



Color generateRandomColor(time_t currtime)
{
	mt19937_64 eng(currtime);
	uniform_int_distribution<int>dis(0, 255);

	return Color{ (unsigned char)dis(eng),(unsigned char)dis(eng),(unsigned char)dis(eng),255 };
}





