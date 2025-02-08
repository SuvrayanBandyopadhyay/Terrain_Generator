#include"Sprite.h"
#include<iostream>
#include<vector>
#include<raylib.h>
using namespace std;
// Loading texture from filename
void Sprite::loadTex(const char* filename)
{

	//Load the texture
	tex = LoadTexture(filename);
	
	SetTextureFilter(tex, TEXTURE_FILTER_ANISOTROPIC_16X);
	SetTextureWrap(tex, TEXTURE_WRAP_CLAMP);
	
	GenTextureMipmaps(&tex);

	//Initialize to default
	scale = 1.0;
	pos = Vector2{ 0,0 };
	rot = 0;

	//Storing our source co-ords
	source.x = 0;
	source.y = 0;
	source.width = tex.width;
	source.height = tex.height;
	
}
void Sprite::loadTex(Texture2D texture)
{
	//Load the texture
	tex = texture;

	//Initialize to default
	scale = 1.0;
	pos = Vector2{ 0,0 };
	rot = 0;

	//Storing our source co-ords
	source.x = 0;
	source.y = 0;
	source.width = tex.width;
	source.height = tex.height;




}
//Loading texture from 

//To set the position
void Sprite::setPos(Vector2 p) 
{
	pos.x = p.x;
	pos.y = p.y;
}

void Sprite::setPos(float x, float y) 
{
	pos.x = x;
	pos.y = y;
}
//To set the rotation
void Sprite::setRot(float rotation) 
{
	rot = rotation;
}
//To set scaling
void Sprite::setScale(float s) 
{
	scale = s;

}

//To draw
void Sprite::draw()
{
	//Creating a destination rectangle
	Rectangle dest;
	dest.x = pos.x;
	dest.y = pos.y;
	dest.width = source.width * (scale+0.01);//0.01 to avoid artifacts
	dest.height = source.height * (scale+0.01);

	//Rotations are always about the central point
	DrawTexturePro(tex, source, dest, Vector2{(float)dest.width/2.0f,(float)dest.height/2.0f}, rot, WHITE);
}
void Sprite::draw(Color c)
{
	//Creating a destination rectangle
	Rectangle dest;
	dest.x = pos.x;
	dest.y = pos.y;
	dest.width = source.width * (scale + 0.01);
	dest.height = source.height*(scale + 0.01);

	//Rotations are always about the central point
	DrawTexturePro(tex, source, dest, Vector2{ (float)dest.width / 2.0f,(float)dest.height / 2.0f }, rot, c);




}

//To get scaling
float Sprite::getScale() 
{
	return scale;
}

//To get position
Vector2 Sprite::setPos() 
{
	return pos;
}

//To play an animation
void Sprite::playAnimation(int id, float deltatime) 
{
	source = animations[id].playAnimation(deltatime);;


}

bool Sprite::pointCollision(Vector2 point) 
{
	//Creating a destination rectangle
	Rectangle dest;
	dest.x = pos.x - (source.width * scale / 2.0);
	dest.y = pos.y - (source.height * scale / 2.0);
	dest.width = source.width * scale;
	dest.height = source.height * scale;






	//Check collsion
	return CheckCollisionPointRec(point, dest);
}