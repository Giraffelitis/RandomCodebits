#include "Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <assert.h>
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Money.h"
#include "Goal.h"
#include "Player.h"
#include "AudioManager.h"
#include "Lava.h"
#include "WaterJug.h"
#include "Teleporter.h"

using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::ifstream;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;
constexpr int kEscapeKey = 27;


Game::Game()
	: m_pStateMachine(nullptr)
{

}

void Game::Initialize(GameStateMachine* pStateMachine)
{
	if (pStateMachine)
	{
		pStateMachine->Init();
		m_pStateMachine = pStateMachine;
	}
}

void Game::RunGameLoop()
{
	bool isGameOver = false;
	while (!isGameOver)
	{
		Update(false);
		Draw();
		isGameOver = Update();
	}
	Draw();
}

void Game::Deinitialize()
{
	if (m_pStateMachine)
	{
		m_pStateMachine->CleanUp();
	}
}

bool Game::Update(bool processInput)
{
	return m_pStateMachine->UpdateCurrentState(processInput);
}

void Game::Draw()
{
	m_pStateMachine->DrawCurrentState();
}
