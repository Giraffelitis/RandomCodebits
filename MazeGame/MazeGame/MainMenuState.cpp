#include "MainMenuState.h"
#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"

using std::cout;
using std::endl;

constexpr int kEscapeKey = 27;

constexpr char kPlay = '1';
constexpr char kHighScores = '2';
constexpr char kSettings = '3';
constexpr char kQuit = '4';

MainMenuState::MainMenuState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{

}

bool MainMenuState::Update(bool processInput)
{
	bool shouldQuit = false;
	if (processInput)
	{
		int input = _getch();
		if (input == kEscapeKey || (char)input == kQuit)
		{
			shouldQuit = true;
		}
		else if ((char)input == kPlay)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Gameplay);
		}
		else if ((char)input == kHighScores)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Highscore);
		}
		else if ((char)input == kSettings)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Settings);
		}
		
	}
	return shouldQuit;
}

void MainMenuState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "           - - - MAIN MENU - - -" << endl << endl;
	cout << "              " << kPlay << ". Play " << endl;
	cout << "              " << kHighScores << ". High Scores " << endl;
	cout << "              " << kSettings << ". Settings " << endl;
	cout << "              " << kQuit << ". Quit " << endl;
}