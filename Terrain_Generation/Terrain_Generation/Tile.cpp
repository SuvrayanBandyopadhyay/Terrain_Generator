#include"Tile.h"
#include<random>
using namespace std;

//Default (no texture)


//Loading tile
Tile::Tile(Texture2D ntex, tileType t)
{
    irrigated = 0;
    river = 0;
	type = t;
	tex = ntex;
    settlementIndex = -1;
    defence = 0;
}

Tile::Tile(char* filename,tileType t)
{
    irrigated = 0;
    river = 0;
	type = t;
	tex = LoadTexture(filename);
    settlementIndex = -1;
    defence = 0;
}



//Setting the source
void Tile::setSource(Rectangle rec) 
{
	source = rec;
}

//Update the tile
void Tile::updateTile(Vector2 mpos,Tile** selector,bool hudhover)
{
    float size = 128;
    if (pointCollision(mpos)&&hudhover==false) //To ensure it isnt hovering over something else
    {
        draw(DARKGRAY);
        //If clicked
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) 
        {
            
            //Set the selector as it self
            *selector = this;

        }
    }

    
    else 
    {
        float shade = 255 - 18 * irrigated;
        Color irr{ shade,shade,shade,255 };
        draw(irr);
    }

    
}

//

//A function to generate rivers in the tilemap
vector<Tile>rivers(vector<Tile>tilemap,vector<vector<double>>map, int minrivers, int maxrivers, int lengthmult,time_t currtime,vector<int>*river_tiles) 
{

    //Size of a tile
    float size = 128;
    //Defining new sources
    Rectangle desertsrc = Rectangle{ 0, 2 * size, size, size };
    Rectangle landsrc = Rectangle{ 0,0,size,size };
    Rectangle snowsrc = Rectangle{ 0,1 * size,size,size };
    Rectangle seasrc = Rectangle{ 0,3 * size,size,size };

    //width and height
    int mapwidth = map[0].size(); 
    int mapheight=map.size();
    //For Randomness
    mt19937_64 eng(currtime);
    uniform_int_distribution<int>river_dis(minrivers, maxrivers);
    uniform_int_distribution<int>x(0, mapwidth - 1);
    uniform_int_distribution<int>y(0, mapheight - 1);
    uniform_real_distribution<float>var(0, 0.1);
    //Chance of river changing constant

    float dirdiv = 20;//Higher value = less turns

    //Number of rivers
    int river_count = river_dis(eng);

    //Now generating rivers
    char dir = 'r';
    for (int i = 0; i < river_count; i++)
    {
        

        //Random starting location
        int r = y(eng);//Row
        int c = x(eng);//Column
        


        while (tilemap[r * mapwidth + c].type == sea || tilemap[r * mapwidth + c].type == ocean)
        {
          
            r = y(eng);//Row
            c = x(eng);//Column

        }
    
        //Changing the boolean values
        tilemap[r * mapwidth + c].river = 1;
        tilemap[r * mapwidth + c].irrigated = 1;
        //Pushing this tile back
        river_tiles->push_back(r * mapwidth + c);

        //Changing the first tile
        //If desert
        if (tilemap[(r * mapwidth) + c].type == desert_hill || tilemap[(r * mapwidth) + c].type == desert_mountain)
        {
            tilemap[r * mapwidth + c].type = desert;
            tilemap[r * mapwidth + c].setSource(desertsrc);
        }
        //If land
        else if (tilemap[r * mapwidth + c].type == hill || tilemap[r * mapwidth + c].type == mountain|| tilemap[r * mapwidth + c].type == forest)
        {
            tilemap[r * mapwidth + c].type = land;
            tilemap[r * mapwidth + c].setSource(landsrc);
        }
        //If snow
        else if (tilemap[r * mapwidth + c].type == snow_hill || tilemap[r * mapwidth + c].type == snow_mountain|| tilemap[r * mapwidth + c].type == snow_forest)
        {
            tilemap[r * mapwidth + c].type = snow;
            tilemap[r * mapwidth + c].setSource(snowsrc);
        }

        


        //Length of river
        int l = map[r][c] * lengthmult * (1 + var(eng));
        
        


        //Generating the river
        for (int j = 0; j < l; j++) 
        {
            

         
            //The weights left right up down
            float l, ri, u, d;

            //Left
            if (c == 0) 
            {
                l = INFINITY;
            }
            else 
            {
                
                l = map[r][c-1];
            }
            //Right
            if (c == mapwidth-1)
            {
                ri = INFINITY;
            }
            else
            {
               
                ri = map[r][c + 1];
            }
            //Up 
            if (r == 0)
            {
                u = INFINITY;
            }
            else
            {
                u = map[r-1][c];
            }
            //Down
            if (r == mapheight - 1)
            {
                d = INFINITY;
            }
            else
            {
                d = map[r+1][c];
            }


            //To make more linear rivers
            
            if (dir == 'r') 
            {
                ri /= dirdiv;
            }
            if (dir == 'l') 
            {
                l = l / dirdiv;
            }
            if (dir == 'u') 
            {
                u = u / dirdiv;
            }
            if (dir == 'd') 
            {
                d = d / dirdiv;
            }
            float ep = 0.001;
            //Create a distribution 
            discrete_distribution<> next_dis{1/(l+ep), 1/(ri+ep), 1/(u+ep), 1/(d+ep)};
            //Find next
            int next = next_dis(eng);

            
            //Moving to next 
            if (next == 0) 
            {
                c--;
                dir = 'l';
            }
            if (next == 1) 
            {
                c++;
                dir = 'r';
            }
            if (next == 2) 
            {
                r--;
                dir = 'u';
            }
            if (next == 3) 
            {
                r++;
                dir = 'd';
            }

            //Changing the tile
           
            //If desert
            if (tilemap[(r * mapwidth) + c].type == desert_hill || tilemap[(r * mapwidth) + c].type == desert_mountain)
            {
                tilemap[r * mapwidth + c].type = desert;
                tilemap[r * mapwidth + c].setSource(desertsrc);
            }
            //If land
            else if (tilemap[r * mapwidth + c].type == hill || tilemap[r * mapwidth + c].type == mountain || tilemap[r * mapwidth + c].type == forest)
            {
                tilemap[r * mapwidth + c].type = land;
                tilemap[r * mapwidth + c].setSource(landsrc);
            }
            //If desert
            else if (tilemap[r * mapwidth + c].type == snow_hill || tilemap[r * mapwidth + c].type == snow_mountain || tilemap[r * mapwidth + c].type == snow_forest)
            {
                tilemap[r * mapwidth + c].type = snow;
                tilemap[r * mapwidth + c].setSource(snowsrc);
            }



            //If ocean/sea break
            else if (tilemap[r * mapwidth + c].type == sea || tilemap[r * mapwidth + c].type == ocean)
            {
                break;
            }
            
            
            //Set river = true
            tilemap[r * mapwidth + c].river = true;
            tilemap[r * mapwidth + c].irrigated = true;
            river_tiles->push_back(r * mapwidth + c);
        }
    }
    return tilemap;
};

//Distance
float dist(Vector2 a, Vector2 b) 
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

//Irrigation check
vector<Tile>irrigate(vector<Tile>Tilemap,vector<int>river_pos)
{
    float size = 128;
    float irr_dist = 2;//Distance to which a river irrigates
    for (int i = 0; i < river_pos.size(); i++) 
    {
        int loc = river_pos[i];
        for (int j = 0; j < Tilemap.size(); j++) 
        {
            if (Tilemap[j].irrigated != 1 && Tilemap[j].type != sea && Tilemap[j].type != ocean) 
            {
                if (dist(Tilemap[j].pos, Tilemap[loc].pos) < size * irr_dist) 
                {
                    Tilemap[j].irrigated = 1;
                }
                else if(dist(Tilemap[j].pos, Tilemap[loc].pos) < size * (irr_dist+2))
                {
                    Tilemap[j].irrigated = 0.75;
                }
                else if(dist(Tilemap[j].pos, Tilemap[loc].pos) < size * (irr_dist+4)&&Tilemap[j].irrigated>0.5)
                {
                    Tilemap[j].irrigated = 0.50;
                }
            }
        
        }

    }
    
    
    return Tilemap;
}


//Convert a vector<vector<double>> to a vector<tile>

vector<Tile>createTileMap(vector<vector<double>> map,vector<vector<double>> precipitation,vector<vector<double>>snow_vec,Texture2D tiletex) 
{
    //Random engines
    mt19937_64 eng(time(NULL));
    uniform_real_distribution<float>err(-0.12, 0.12);

    vector<Tile>tilemap;
    float size = 128;
    float dry = 0.32;
    float snow_limit = 0.245;
    float rain = 0.8;
    //Do nescessary conversions
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            tileType t = land;
            Rectangle src;

            //if no snow
            if (snow_vec[i][j] < snow_limit)
            {
                if (map[i][j] < 0.44)
                {
                    t = ocean;
                    src = Rectangle{ 1 * size ,3 * size,size,size };

                }
                else if (map[i][j] < 0.48)
                {
                    t = sea;
                    src = Rectangle{ 0 * size,3 * size,size,size };
                }
                else if (map[i][j] < 0.88)
                {
                    if (precipitation[i][j] < dry)
                    {
                        t = desert;
                        src = Rectangle{ 0, 2 * size, size, size };
                    }
                    else if (precipitation[i][j] < rain)
                    {
                        t = land;
                        src = Rectangle{ 0,0,size,size };
                    }
                    else
                    {
                        t = forest;
                        src = Rectangle{ 3 * size,0,size,size };
                    }
                }
                else if (map[i][j] < 0.92)
                {
                    if (precipitation[i][j] < dry)
                    {
                        t = desert_hill;
                        src = Rectangle{ 1 * size, 2 * size, size, size };
                    }
                    else
                    {
                        t = hill;
                        src = Rectangle{ 1 * size,0,size,size };
                    }

                }
                else
                {
                    if (precipitation[i][j] < dry)
                    {
                        t = desert_mountain;
                        src = Rectangle{ 2 * size, 2 * size, 128, 128 };
                    }
                    else
                    {
                        t = mountain;
                        src = Rectangle{ 2 * size,0,128,128 };
                    }
                }
            }
           
            //If snow
            else 
            {
                if (map[i][j] < 0.44)
                {
                    t = ocean;
                    src = Rectangle{ 1 * size ,3 * size,size,size };

                }
                else if (map[i][j] < 0.48)
                {
                    t = sea;
                    src = Rectangle{ 0 * size,3 * size,size,size };
                }
                else if (map[i][j] < 0.88)
                {
                 
                    if (precipitation[i][j] < rain)
                    {
                        t = snow;
                        src = Rectangle{ 0,1*size,size,size };
                    }
                    else
                    {
                        t = snow_forest;
                        src = Rectangle{ 3 * size,1*size,size,size };
                    }
                }
                else if (map[i][j] < 0.92)
                {
                    
                    
                    t = snow_hill;
                    src = Rectangle{ 1 * size,1*size,size,size };
                    

                }
                else
                {
                   
                    
                    t = snow_mountain;
                    src = Rectangle{ 2 * size,1*size,size,size };
                    
                }
            }


            //To much precipitation.. sea formation
            /*if (precipitation[i][j] > 0.93 && t != ocean)
            {
                t = sea;
                src = Rectangle{ 0,3*size,size,size };
                cout << j << "," << i << endl;
            }
            */
            Tile newtile(tiletex, t);
            newtile.setPos(j * size, i * size);
            newtile.setSource(src);
            newtile.setScale(1);

            ///SETTING DEFENCE
            //Setting the  base defence of the tile
            float minpower = 5;
            float maxpower = 3;
           

            float height = map[i][j];
            uniform_real_distribution<float> dis(pow(height, minpower), pow(height, maxpower));

            newtile.defence = dis(eng);
            //Now Setting extra defence due to rain
            float rain = precipitation[i][j];
            uniform_real_distribution<float> raindis(pow(rain, minpower), pow(rain, maxpower));
            newtile.defence *= (1 + raindis(eng));
            //Adding error
            newtile.defence *= (1 + err(eng));

            tilemap.push_back(newtile);

        }
    }
    //Now we generate rivers
    vector<int>river_pos;

    
    tilemap = rivers(tilemap, map, (int)(map[0].size()/13), (int)(map[0].size() / 8), 150, time(NULL),&river_pos);
    
    
    //Now we irrigate tiles
    tilemap = irrigate(tilemap,river_pos);//Time consuming
    //Remember to put it back

    return tilemap;
}

