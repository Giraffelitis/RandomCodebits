#include "WinState.h"
#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"

using std::cout;
using std::endl;

WinState::WinState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{

}

bool WinState::Update(bool processInput)
{
	if (processInput)
	{
		int input = _getch();
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);	
	}
	return false;
}

void WinState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "           - - - WELL DONE - - -" << endl << endl;
	cout << "           You beat the maze!" << endl;
	cout << "           Press any key to return to Main Menu" << endl;
	
}