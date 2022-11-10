#pragma once
#include "Card.h"
#include <string>
#include <windows.h>

using std::cout;
using std::endl;

class Player
{
public:
	Player();
	~Player();	
	
	int PlayOneCard();
	int PlayThreeCards();
	void AddCardToStack(vector<Card*> stack, Card* card);
	void TakeCardsWon(Player& loser);
	void ReturnCardsToDeck(vector<Card*> deck);
	int GetNumOfCards() { return (int)m_pHand.size() + (int)m_pDiscardPile.size(); }

	vector<Card*> m_pHand;
	
private:	
	void DisplayCard(Card* card);
	void SetCardColor(Card* card);
	void RecycleDiscardPile();

	vector<Card*> m_pCardsUsed;
	vector<Card*> m_pDiscardPile;
};
