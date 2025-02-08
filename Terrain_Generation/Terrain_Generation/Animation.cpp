#include"Animation.h"
#include<string>
using namespace std;


//Initially keep clock as zero 
Animation::Animation() 
{
	clock = 0;
	current = 0;

}
//Manually set a frame
void Animation::setFrame(int id) 
{
	current = id;
	clock = 0;
}
//Add keyframes
void Animation::addKeyframe(keyframe key) 
{
	keyframes.push_back(key);
}

//Play animation
Rectangle Animation::playAnimation(float deltatime) 
{
	if (keyframes.size() == 0) 
	{
		printf("ERROR ANIMATION DOES NOT EXIST\n");
		return Rectangle{0,0,0,0};
	}
	else 
	{
		clock += deltatime;
	}

	//Move to next frame
	if (clock > keyframes[current].time) 
	{
		current++;
		clock = 0;

		//If current is greater than number of keyframes,revert to one
		if (current >= keyframes.size()) 
		{
			current = 0;
		}
		;
	}

	return keyframes[current].frame;
}
//Load animation from a .anim file

void Animation::loadAnimation(char* filename) 
{
	fstream file((const char*)filename);
	
	string input;
	//If file does not exist
	if (!file) 
	{
		cout << "ERROR::FILE " << filename << " DOES NOT EXIST" << endl;
	}

	//While lines exist
	while (getline(file, input)) 
	{
		//Add a new keyframe
		Rectangle rect;
		float time;
		sscanf_s(input.c_str(), "%f %f %f %f %f", &rect.x, &rect.y, &rect.width, &rect.height, &time);
		//Now adding a new keyframe
		keyframe key;
		key.frame = rect;
		key.time = time;
		addKeyframe(key);
	}
}
//Set time
void Animation::setclock(float t) 
{
	clock = t;
}