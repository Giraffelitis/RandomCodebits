#include <iostream>
#include <windows.h>
#include "Teleporter.h"

void Teleporter::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);
		
	if (m_renderState == 0)
	{
		std::cout << 'O';
		m_renderState++;
	}
	else if (m_renderState == 1)
	{
		std::cout << 'o';
		m_renderState--;
	}

	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}
