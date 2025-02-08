#include<iostream>
#include"Sprite.h"
#include"Settlement.h"
#include"SettlementMenu.h"

using namespace std;

void SettlementMenu::load(ResourceHandler handler) 
{
	for (int i = 0; i < 4; i++) 
	{
		recruitButton[i].loadTex(handler.recruitButton);
		recruitButton[i].pos.x = 100 + i * 200;
		recruitButton[i].pos.y = 800;
	}

	//Set the screen;
	recruitmentScreen.loadTex(handler.recruitScreen);
	recruitmentScreen.setPos(800, 800);
}

//Update the settlement

void SettlementMenu::update(Settlement s,Vector2 hudpos) 
{
	//Draw a box as the background
	DrawRectangle(50, 50, 1000, 1000, DARKGRAY);

	//Draw the recruit screen
	recruitmentScreen.draw();
	//Update and Draw all recruit button
	for (int i = 0; i < 4; i++) 
	{
		recruitButton[i].updateButton(hudpos);
		recruitButton[i].draw();

	}

}