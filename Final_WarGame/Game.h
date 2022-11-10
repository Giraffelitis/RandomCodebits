#pragma once
#include <assert.h>
#include "Deck.h"
#include "Player.h"

using std::cin;

class Game
{
public:
	Game(int& numOfPlayers, int& numOfRounds, int& m_totalRounds, bool& m_showRounds, bool& isManual);
	~Game();

	void PlayGame(bool& isGameOver, int& pOneWins, int& pTwoWins, int& draw, int& totalNumOfRounds, int& longRounds, int& shortRounds);
	void ResetGame(bool& isGameOver);

private:
	void PlayRound(Player& playerOne, Player& playerTwo, bool& isGameOver);
	void GivePlayersCards(Deck& deck);
	bool PlayFirstHand(Player& playerOne, Player& playerTwo);
	void PlayWarHands(Player& playerOne, Player& playerTwo, bool& isGameOver);
	void CheckPlayerHandSize(Player& playerOne, Player& playerTwo, bool& isGameOver);
	void EndOfGame(int& pOneWins, int& pTwoWins, int& draw, int& totalNumOfRounds, int& longRounds, int& shortRounds);
	void PressEnterToContinue();

	int m_numOfRounds;
	int m_totalNumOfRounds;
	bool m_isDraw;
	bool m_isGameOver;
	int m_playerOneCardValue;
	int m_playerTwoCardValue;
	bool m_playerOneVictory;
	bool m_playerTwoVictory;
	bool m_showRounds;
	int m_numOfPlayers;
	bool m_isManual;

	Deck m_deck;
	Player m_pPlayerArray[2];
};