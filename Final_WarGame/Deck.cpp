#include <algorithm>
#include <random>
#include <assert.h>
#include "Deck.h"
#include "Player.h"
 
Deck::Deck()
{
	//Build deck of cards using # of Suits and # of Values per suit
	for (int suit = (int)CardSuit::begin; suit <= (int)CardSuit::end; suit++)
	{
		for (int value =(int)CardValue::begin; value <= (int)CardValue::end; value++)
		{
			m_pDeck.push_back(new Card(CardSuit(suit), CardValue(value)));
		}
	}
}

	//Clean up on game close
Deck::~Deck()
{
	while (!m_pDeck.empty())
	{
		delete m_pDeck.back();
		m_pDeck.pop_back();
	}	
}

//Shuffle the deck
void Deck::ShuffleCards()
{
	std::random_device rd;
	std::shuffle(std::begin(m_pDeck), std::end(m_pDeck), rd);
}

// Split the deck and give cards to players
void Deck::DealCards(Player& playerOne, Player& playerTwo)
{
	int it = 0;
	for (int i = 0; i < m_pDeck.size(); i++, it++ )
	{
		if (it % 2 == 0)
		{
			playerOne.AddCardToStack(playerOne.m_pHand, m_pDeck[i]);
		}
		else
		{
			playerTwo.AddCardToStack(playerTwo.m_pHand, m_pDeck[i]);
		}			
	}
}
