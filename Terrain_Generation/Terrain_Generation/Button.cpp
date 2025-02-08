#include"Button.h"

void Button::updateButton(Vector2 mpos) 
{
	//Reset boolean values
	isHover = false;
	isClicked = false;


	//If hovering
	if(pointCollision(mpos))
	{
		isHover = true;
		//Now if mouse key is released
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) 
		{
			isClicked = true;
		}
	}
}