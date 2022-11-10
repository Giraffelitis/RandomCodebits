#include "LoseState.h"
#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"

using std::cout;
using std::endl;

LoseState::LoseState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{

}

bool LoseState::Update(bool processInput)
{
	if (processInput)
	{
		int input = _getch();
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
	}
	return false;
}

void LoseState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "           - - - GAME OVER - - -" << endl << endl;
	cout << "           Better Luck Nexxt Time" << endl;
	cout << "           Press any key to return to Main Menu" << endl;

}