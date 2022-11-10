#pragma once
#include "Card.h"
#include "Player.h"

using std::cout;
using std::endl;

class Deck
{
public:
	Deck();
	~Deck();

	void ShuffleCards();
	void DealCards(Player& playerOne, Player& playerTwo);
	std::vector<Card*> m_pDeck;
};