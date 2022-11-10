#include <iostream>
#include <windows.h>
#include "Door.h"

Door::Door(int x, int y, ActorColor color, ActorColor closedColor)
	: PlaceableActor(x, y, color)
	, m_isOpen(false)
	, m_closedColor(closedColor)
{

}

//Prints door to console and changes color based on if its open or closed
void Door::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_isOpen)
	{
		SetConsoleTextAttribute(console, (int)m_color);
	}
	else
	{
		SetConsoleTextAttribute(console, (int)m_closedColor);
	}
	std::cout << "|";		//TODO Make it check for Vertical / Horizontal
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}