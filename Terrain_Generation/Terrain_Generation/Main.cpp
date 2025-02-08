#include "raylib.h"
#include<iostream>
#include<vector>

#include"Sprite.h"
#include"Renderer.h"
#include"Tile.h"
#include"MapGen.h"
#include"GameEngine.h"

#define RENDER_WIDTH 1920
#define RENDER_HEIGHT 1120
using namespace std;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
   
    //Open full screen window
    startWindow();

    //Load the game
    GameEngine game(RENDER_WIDTH, RENDER_HEIGHT);
    game.load();
   
    //Run the game 
    game.run();

  
    //Close the window
    CloseWindow();    
    //End
    return 0;
}