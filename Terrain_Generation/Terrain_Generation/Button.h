#pragma once
#include"Sprite.h"

//A button is basically a sprite with 2 additional members... hover(To check if mouse is hovering on it) and is_pressed(if it is clicked)
class Button :public Sprite 
{
protected:
	


public:
	//Is it hovering
	bool isHover = false;

	//Has the button been clicked
	bool isClicked = false;
	//An extra function to convert the sprite into a button
	//Should be run before the draw call
	void updateButton(Vector2 mpos);

};