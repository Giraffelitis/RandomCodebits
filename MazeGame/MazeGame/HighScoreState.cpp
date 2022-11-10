#include "HighScoreState.h"
#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"
#include "Utility.h"

using std::cout;
using std::endl;

HighScoreState::HighScoreState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
	m_Highscores = Utility::WrtieHighScore(0);
}

bool HighScoreState::Update(bool processInput)
{
	if (processInput)
	{
		int input = _getch();
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
	}
	return false;
}
void HighScoreState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "           - - - HIGH SCORES - - -" << endl << endl;
	for (auto i = m_Highscores.rbegin(); i != m_Highscores.rend(); ++i)
	{
		cout << "          " << *i << endl;
	}
	cout << endl << endl;
	cout << "          Press any key to return to Main Menu." << endl;
}