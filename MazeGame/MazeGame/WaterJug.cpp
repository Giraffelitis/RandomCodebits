#include <iostream>
#include <windows.h>
#include "WaterJug.h"

void WaterJug::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);

	std::cout << (char)254;	
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}
