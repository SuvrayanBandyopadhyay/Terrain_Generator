#include"GameEngine.h"

using namespace std;

//A function to start the window
void startWindow() 
{
	// Initialization
	//--------------------------------------------------------------------------------------
	InitWindow(0,0, "raylib [core] example - basic window");
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	SetConfigFlags(FLAG_WINDOW_UNDECORATED);
	//Disable cursor
	HideCursor();

	//Setting FPS
	SetTargetFPS(120);
}


//Initialization
GameEngine::GameEngine(int render_width,int render_height):GameRender(render_width,render_height)
{
	

	SetMouseScale(1.0, 1.0);
	state = 0;
	
}
//Loading
//The load function
void GameEngine::load()
{
	
	//Loading resources
	resources.load();
	//Loading the cursor
	cursor.loadTex(resources.cursortex);
	cursor.setScale(1.2);

	menu.setup(resources.newgametex, resources.loadgametex, resources.settingstex, resources.creditstex, resources.tiletex);
	GameRender.cam.target = Vector2{ 0,0};
	
}
void::GameEngine::updateCursor(Vector2 mpos) 
{
	cursor.pos = mpos;

	//To make it independent of zoom
	cursor.setScale(1.2 / GameRender.cam.zoom);

	//Since the cursor is drawn at the center, but we want the tip
	cursor.pos.y += 16 / GameRender.cam.zoom;
}

void GameEngine::run() 
{
	while (!WindowShouldClose())
	{

		//First of all... the draw command
		GameRender.startRender();
		//Mouse Position
		Vector2 mpos = GameRender.getConvertedMousePosition();
		//Update the cursor
		updateCursor(mpos);

		//Now the various cases
		if (state == 0)
		{
			//Get mouse postition wrt render screen
			
			//setting game camera
			
			state = menu.run(mpos);
			
		}
		
		//Load the game
		if (state == 1) 
		{
			//Load the game
			thread loadthread(&GameHandler::load,&this->game, 6,resources,time(NULL),&GameRender.cam);
			//Detach the thread so that it runs in the background
			loadthread.detach();
			state = 5;
		}
		//Play the game and loading
		if (state == 5)
		{
			
			//If not loaded
			if (game.isloaded == false)
			{
				GameRender.cam.target = Vector2{ 0,0 };
				//Display the loading screen
				game.loadingscreen();
			
			}
			


			//If loaded
			else 
			{
				//Update the camera
				GameRender.updateGameCamera();
			


				//Run the game
				game.run(GameRender.getConvertedMousePosition(),GameRender.cam.target,GameRender.getRenderWidth(),GameRender.getRenderHeight());
			
			}
		}

		//Reactivate Camera for the cursor
		BeginMode2D(GameRender.cam);
		//Draw the cursor
		cursor.draw();
		
	


		GameRender.endRender();
	}
}