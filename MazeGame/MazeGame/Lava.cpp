#include <iostream>
#include <windows.h>
#include "Lava.h"

Lava::Lava(int x, int y, ActorColor color, ActorColor disabledColor)
	: PlaceableActor(x, y, color)
	, m_isDisabled(false)
	, m_disabledColor(disabledColor)
{
	
}

//Prints door to console and changes color based on if its open or closed
void Lava::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!m_isDisabled)
	{
		SetConsoleTextAttribute(console, (int)m_color);
		if (m_renderState == 0)
		{
			std::cout << (char)177;
			m_renderState++;
		}
		else
		{
			std::cout << (char)178;
			m_renderState--;
		}
	}
	else
	{
		SetConsoleTextAttribute(console, (int)m_disabledColor);
		std::cout << (char)177;		
	}		
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}