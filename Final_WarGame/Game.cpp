#include "Game.h"
#include <limits>

Game::Game(int& numOfPlayers, int& numOfRounds, int& totalRounds, bool& showRounds, bool& isManual)
	: m_isDraw(false)
	, m_isGameOver(false)
	, m_numOfRounds(numOfRounds)
	, m_playerOneCardValue(0)
    , m_playerTwoCardValue(0)
	, m_playerOneVictory(false)
	, m_playerTwoVictory(false)
	, m_showRounds(showRounds)
	, m_totalNumOfRounds(totalRounds)
	, m_numOfPlayers(numOfPlayers)
	, m_pPlayerArray()
	, m_deck()
	, m_isManual(isManual)
{

}

Game::~Game()
{	

}

	// Build the game and loops through rounds until a winner is determined and triggers End of Game
void Game::PlayGame(bool& isGameOver, int& pOneWins, int& pTwoWins, int& draw, int& totalNumOfRounds, int& longRounds, int& shortRounds)
{
	GivePlayersCards(m_deck);

	while (!isGameOver)
	{
		PlayRound(m_pPlayerArray[0], m_pPlayerArray[1], isGameOver);
	}

	EndOfGame(pOneWins, pTwoWins, draw, totalNumOfRounds, longRounds, shortRounds);
}

	//shuffle deck and deal card to each player
void Game::GivePlayersCards(Deck& deck)
{
	deck.ShuffleCards();
	deck.DealCards(m_pPlayerArray[0], m_pPlayerArray[1]);
}

void Game::PlayRound(Player& playerOne, Player& playerTwo, bool& isGameOver)
{
	m_totalNumOfRounds++;
	m_numOfRounds++;

	if (m_showRounds)
	{
		cout << "***** ROUND " << m_numOfRounds << " ******" << endl;
	}

	// Display number of cards each person has to begin the round
	if (m_showRounds)
	{
		cout << "*** # of cards ***" << endl;
		cout << "P1: " << playerOne.GetNumOfCards() << "   P2: " << playerTwo.GetNumOfCards() << endl;
	}
	//Play the first card of the round
	PlayFirstHand(playerOne, playerTwo);

	//Check if the first cards played are equal and if both players still have cards in thier hand
	if (m_playerOneCardValue == m_playerTwoCardValue)
	{
			if (m_showRounds)
			{
				cout << "  <-- WAR!!!" << endl;
			}
			if (m_isManual)
			{
				cout << endl;
				cout << "Play WAR hands" << endl;
				PressEnterToContinue();
			}
			PlayWarHands(playerOne, playerTwo, isGameOver);
	}

	// if player one has the highest card Player one wins the hand 
	if (m_playerOneCardValue > m_playerTwoCardValue)
	{
		if (m_showRounds)
		{
			cout << endl;
			cout << "Player 1 Wins the hand." << endl;
		}
		playerOne.TakeCardsWon(playerTwo);
		cout << endl;
	}

	// if player two has the highest card oPlayer two wins the hand
	else if (m_playerOneCardValue < m_playerTwoCardValue)
	{
		if (m_showRounds)
		{
			cout << endl;
			cout << "Player 2 Wins the hand." << endl;
		}
		playerTwo.TakeCardsWon(playerOne);
		cout << endl;
	}
	CheckPlayerHandSize(playerOne, playerTwo, isGameOver);
	if (m_isManual)
	{
		PressEnterToContinue();
		system("cls");
	}
}

//Each player playes one card
bool Game::PlayFirstHand(Player& playerOne, Player& playerTwo)
{
	if (m_isManual)
	{
		cout << "To play next hand" << endl;
		PressEnterToContinue();
	}
	if (m_showRounds)
	{
		cout << "  ";
	}
	m_playerOneCardValue = playerOne.PlayOneCard();
	if (m_showRounds)
	{
		cout << "    ";
	}
	m_playerTwoCardValue = playerTwo.PlayOneCard();

	return m_playerOneCardValue == m_playerTwoCardValue;
}

// Each player plays three cards if available
void Game::PlayWarHands(Player& playerOne, Player& playerTwo, bool& isGameOver)
{
	do 
	{
		m_playerOneCardValue = playerOne.PlayThreeCards();

		if (m_showRounds)
		{
			cout << "  ";
		}

		m_playerTwoCardValue = playerTwo.PlayThreeCards();
		
		if(m_playerOneCardValue == m_playerTwoCardValue)
		{
			if (m_showRounds)
			{
				cout << "  <-- WAR!!!" << endl;
			}
			CheckPlayerHandSize(playerOne, playerTwo, isGameOver);
		}
	} while (m_playerOneCardValue == m_playerTwoCardValue && !isGameOver);
}

	//Check player hands to see if they are out of cards
void Game::CheckPlayerHandSize(Player& playerOne, Player& playerTwo, bool& isGameOver)
{
	if (playerOne.GetNumOfCards() == 0 && playerTwo.GetNumOfCards() == 0)
	{
		isGameOver = true;
	}
	else if (playerOne.GetNumOfCards() == 0)
	{
		isGameOver = true;
		m_playerTwoVictory = true;
	}
	else if (playerTwo.GetNumOfCards() == 0)
	{
		isGameOver = true;
		m_playerOneVictory = true;
	}
}

	//Print end of game results 
void Game::EndOfGame(int& pOneWins, int& pTwoWins, int& draw, int& totalNumOfRounds, int& longRounds, int& shortRounds)
{
	if (m_playerOneVictory)
	{
		cout << endl;
		cout << "Player Two is out of cards." << endl;
		cout << "Player One Wins" << endl;
		cout << "# of Rounds " << m_numOfRounds << endl;
		pOneWins++;
	}
	else if (m_playerTwoVictory)
	{
		cout << endl;
		cout << "Player One is out of cards." << endl;
		cout << "Player Two Wins" << endl;
		cout << "# of Rounds " << m_numOfRounds << endl;
		pTwoWins++;
	}
	else
	{
		cout << endl;
		cout << "The game ended in a draw..." << endl;
		cout << "# of Rounds " << m_numOfRounds << endl;
		draw++;
	}
	// calculate & update round variables
	totalNumOfRounds += m_numOfRounds;
	if (m_numOfRounds > longRounds)
	{
		longRounds = m_numOfRounds;
	}
	if (m_numOfRounds < shortRounds)
	{
		shortRounds = m_numOfRounds;
	}
}

	//Reset game settings for start next game 
void Game::ResetGame(bool& isGameOver)
{
	m_numOfRounds = 0;
	isGameOver = false;
	m_playerOneVictory = false;
	m_playerTwoVictory = false;
	m_pPlayerArray[0].ReturnCardsToDeck(m_deck.m_pDeck);
	m_pPlayerArray[1].ReturnCardsToDeck(m_deck.m_pDeck);
}

void Game::PressEnterToContinue()
{
	system("pause");
}