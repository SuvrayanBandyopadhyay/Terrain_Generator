#pragma once
#include<raylib.h>
#include<iostream>
#include<vector>
#include"Animation.h"

class Sprite
{
protected:
	//All the things we need in order to define our Sprite
	float scale;
	Rectangle source;
	Texture2D tex;
public:
	
	Vector2 pos;
	float rot;

	//To load a new texture
	void loadTex(const char* filename);
	void loadTex(Texture2D texture);
	//To set position
	void setPos(Vector2 p);
	void setPos(float x, float y);
	//To set rotation
	void setRot(float rotation);
	//To set scale
	void setScale(float s);
	//To get position
	Vector2 setPos();
	



	//To draw
	void draw();
	//To draw with a tint
	void draw(Color c);

	//To get scale
	float getScale();

	//All the animations
	std::vector<Animation>animations;
	//Play animation
	void playAnimation(int id,float deltatime);
	//check collision
	bool pointCollision(Vector2 point);

};