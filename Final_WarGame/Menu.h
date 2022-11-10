#pragma once
#include <string>
#include <iostream>
#include <limits>

using std::string;
using std::cout;
using std::endl;
using std::cin;

class Menu
{
public: 
	Menu();
	~Menu();

	void MainMenu(int& numOfGames, bool& showRounds, bool& isManual, bool& keepPlaying);
	bool YesOrNoPrompt();

private:	
	void ListRules(int& numOfGames, bool& showRounds, bool& isManual, bool& keepPlaying);
	void GameMode(int& numOfGames, bool& showRounds, bool& isManual, bool& keepPlaying);
	void NumberOfGames(int& numOfGames, bool& showRounds);
	void AutomaticOptions(int& numOfGames, bool& showRounds, bool& isManual, bool& keepPlaying);
	bool ValidateInput(int& select, int menuSize);
	void PressEnterToContinue();

	int m_selection;
	int m_numOfGames;
	int m_menuSize;
	bool m_isManual;
	bool m_showRounds;
	bool m_keepPlaying;
	bool m_isValid;
};
