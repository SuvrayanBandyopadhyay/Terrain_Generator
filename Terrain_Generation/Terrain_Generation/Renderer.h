#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<raylib.h>
#include"Sprite.h"
;
//We define our screen co-ordinates...All other screen resolutions will be clamped versions of this



class Renderer 
{
private:
	//The texture to which we will draw 
	RenderTexture render;
	

public:
	//The camera
	Camera2D cam;

	Renderer(int render_width,int render_height);
	void startRender();

	//Just adds another sprite to the draw line
	//Sprites with a lower y value(on top) are drawn first..
	//one can change this order by using the second function
	void drawsprite(Sprite s);
	
	void endRender();
	//Update game camera
	void updateGameCamera();


	//To get converted mouse position with regards to the renderscreen (Mouse coords generally given wrt screen)
	Vector2 getConvertedMousePosition();

	//RenderWidth
	int getRenderWidth();
	//RenderHeight
	int getRenderHeight();
};
