#include <iostream>
#include <assert.h>
#include <windows.h>
#include <fstream>
#include "Level.h"
#include "Door.h"
#include "Player.h"
#include "Goal.h"
#include "Money.h"
#include "Enemy.h"
#include "Key.h"
#include "Lava.h"
#include "WaterJug.h"
#include "Teleporter.h"

using std::ifstream;
using std::cout;
using std::endl;
using std::string;

Level::Level()
	: m_pLevelData(nullptr)
	, m_height(0)
	, m_width(0)
{

}

Level::~Level()
{
	if (m_pLevelData != nullptr)
	{
		delete[] m_pLevelData;
		m_pLevelData = nullptr;
	}

	while (!m_pActors.empty())
	{
		delete m_pActors.back();
		m_pActors.pop_back();
	}
}

bool Level::Load(string levelName, int* playerX, int* playerY)
{
	levelName.insert(0, "../");
	ifstream levelFile;
	levelFile.open(levelName);
	if (!levelFile)
	{
		cout << "No file found" << endl;
		return false;
	}
	else
	{
		constexpr int tempSize = 64;
		char temp[tempSize];

		levelFile.getline(temp, tempSize, '\n');
		m_width = atoi(temp);

		levelFile.getline(temp, tempSize, '\n');
		m_height = atoi(temp);

		m_pLevelData = new char[m_width * m_height];
		levelFile.read(m_pLevelData, m_width * m_height);
		
		bool anyWarnings = Convert(playerX, playerY);
		if (anyWarnings)
		{
			cout << "There are some warnings in the level data, see above." << endl;
			system("pause");
		}
		return true;
	}
}

void Level::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);

	//Draw the level
	for (int y = 0; y < GetHeight(); ++y)
	{
		for (int x = 0; x < GetWidth(); ++x)
		{
			int indexToPrint = GetIndexFromCoordinates(x, y);
			cout << m_pLevelData[indexToPrint];
		}
		cout << endl;
	}

	COORD actorCursorPosition;

	//Draw Actors

	for (auto actor = m_pActors.begin(); actor != m_pActors.end(); ++actor)
	{
		if ((*actor)->IsActive())
		{
			actorCursorPosition.X = (*actor)->GetXPosition();
			actorCursorPosition.Y = (*actor)->GetYPosition();
			SetConsoleCursorPosition(console, actorCursorPosition);
			(*actor)->Draw();
		}
	}
}

bool Level::IsSpace(int x, int y)
{
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == ' ';
}

bool Level::IsWall(int x, int y)
{
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == WAL;
}

bool Level::Convert(int* playerX, int* playerY)
{
	bool anyWarnings = false;
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			int index = GetIndexFromCoordinates(x, y);
			
			switch (m_pLevelData[index])
			{
			case '+':
			case '-':
			case '|':
				m_pLevelData[index] = WAL;
				break;
			case 'r':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Key(x, y, ActorColor::Red));
				break;
			case 'g':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Key(x, y, ActorColor::Green));
				break;
			case 'b':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Key(x, y, ActorColor::Blue));
				break;
			case 'R':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Door(x, y, ActorColor::Red, ActorColor::SolidRed));
				break;
			case 'G':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Door(x, y, ActorColor::Green, ActorColor::SolidGreen));
				break;
			case 'B':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Door(x, y, ActorColor::Blue, ActorColor::SolidBlue));
				break;
			case 'X':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Goal(x, y));
				break;
			case '$':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Money(x, y, 1 + rand() % 5));
				break;
			case '@':
				m_pLevelData[index] = ' ';
				if (playerX != nullptr && playerY != nullptr)
				{
					*playerX = x;
					*playerY = y;
				}
				break;
			case 'L':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Lava(x, y, ActorColor::Orange, ActorColor::Purple));
				break;
			case 'W':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new WaterJug(x, y, ActorColor::Cyan));
				break;
			case '1':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Teleporter(x, y, ActorColor::Blue));
				break;
			case '2':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Teleporter(x, y, ActorColor::Red));
				break;
			case '3':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Teleporter(x, y, ActorColor::Green));
				break;
			case '4':
				m_pLevelData[index] = ' ';
				m_pActors.push_back(new Teleporter(x, y, ActorColor::Purple));
				break;
			case 'e':
				m_pActors.push_back(new Enemy(x, y));
				m_pLevelData[index] = ' '; //clear level data				
				break;
			case 'h':
				m_pActors.push_back(new Enemy(x, y, 3, 0));
				m_pLevelData[index] = ' '; //clear level data				
				break;
			case 'v':
				m_pActors.push_back(new Enemy(x, y, 0, 2));
				m_pLevelData[index] = ' '; //clear level data				
				break;
			case 's':
				m_pActors.push_back(new Enemy(x, y, 3, 3));
				m_pLevelData[index] = ' '; //clear level data				
				break;
			case ' ':
				break;
			default:
				cout << "invalid character in level file : " << m_pLevelData[index] << endl;
				anyWarnings = true;
				break;
			}
		}
	}
	return anyWarnings;
}

int Level::GetIndexFromCoordinates(int x, int y)
{
	return x + y * m_width;
}

//Updates all actors and returns a colliding actor if there is one
PlaceableActor* Level::UpdateActors(int x, int y)
{
	PlaceableActor* collidedActor = nullptr;

	for (auto actor = m_pActors.begin(); actor != m_pActors.end(); ++actor)
	{
		(*actor)->Update(); //Update all actors

		if (x == (*actor)->GetXPosition() && y == (*actor)->GetYPosition())
		{
			//should only be able to collide with one actor
			assert(collidedActor == nullptr);
			collidedActor = (*actor);
		}
	}
	return collidedActor;
}