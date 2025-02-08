#pragma once
#include<raylib.h>
#include<iostream>
#include<vector>
#include<fstream>

struct keyframe 
{
	Rectangle frame;
	float time;
};

class Animation 
{
private:
	float clock;
	std::vector<keyframe>keyframes;
	int current;
public:

	//Constructor
	Animation();
	//Returns the current animation
	Rectangle playAnimation(float deltatime);
	//Set the frame
	void setFrame(int id);
	//Adds a keyframe
	void addKeyframe(keyframe key);
	//Loads animation from a .anim file (stores x y width height time)
	void loadAnimation(char* filename);
	//Set clock(Used while switching animations)
	void setclock(float t);
};