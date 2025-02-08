#include"raylib.h"
#include"Renderer.h"
//Some Macros


using namespace std;
//My resolution 1920,1200

//Initialization
Renderer::Renderer(int render_width,int render_height) 
{
	render = LoadRenderTexture(render_width, render_height);

	cam = { 0 };
	cam.target = Vector2{ 0,0};
	cam.zoom = 1.0;
	cam.rotation = 0;
	cam.offset = Vector2{ 0,0 };
}

//To start the rendering
void Renderer::startRender()
{

	//We want to draw to this render texture... so we do that
	BeginTextureMode(render);
	
	//Clearing the background with white
	ClearBackground(WHITE);
	BeginMode2D(cam);


	
}
//To add a sprite to render
void Renderer::drawsprite(Sprite s) 
{
	//Just draw it 
	s.draw();
}
//Ending the render and displaying on the screen
void Renderer::endRender()
{
	//End camera
	EndMode2D();
	//End texture mode
	EndTextureMode();
	

	//Draw the rectangle to our screen
	//Source Rectangle
	//Flipping the texture
	Rectangle source = Rectangle{ 0,0,(float)render.texture.width,-(float)render.texture.height };
	Rectangle dest = Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};

	BeginDrawing();
	ClearBackground(BLACK);
	//Now we draw it
	DrawTexturePro(render.texture, source, dest,Vector2{0,0}, 0, WHITE);

	
	EndDrawing();
}

Vector2 Renderer::getConvertedMousePosition()
{
	//Mouse x position
	float mx = ((GetMousePosition().x) / ((float)GetScreenWidth())) * (float)render.texture.width*(1.0/cam.zoom);
	//Mouse y position
	float my = ((GetMousePosition().y) / ((float)GetScreenHeight())) * (float)render.texture.height*(1.0/cam.zoom);
	
	mx += cam.target.x;
	my += cam.target.y;
	
	return Vector2{ mx,my };
}

//Update the game camera
void Renderer::updateGameCamera() 
{
	float camspeed = 2400 / (1 + cam.zoom);

	//Camera Movement
	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) 
	{
		cam.target.y -= camspeed * GetFrameTime();
	}

	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
	{
		cam.target.x -= camspeed * GetFrameTime();
	}

	if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
	{
		cam.target.y += camspeed * GetFrameTime();
	}

	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
	{
		cam.target.x += camspeed * GetFrameTime();
	}


	//Camera Zoom
	float zoomspeed = 0.05*cam.zoom;
	cam.zoom += GetMouseWheelMove() * zoomspeed;
	if (cam.zoom < 0.25) 
	{
		cam.zoom = 0.25;
	}
	if (cam.zoom > 5) 
	{
		cam.zoom = 5;
	}

}

int Renderer::getRenderHeight() 
{
	return render.texture.height;
}

int Renderer::getRenderWidth()
{
	return render.texture.width;
}