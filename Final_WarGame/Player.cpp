#include <algorithm>
#include <random>
#include "Player.h"
#include <assert.h>

constexpr int k_warHandSize = 3;

Player::Player()	
{
}

Player::~Player()
{
	while (!m_pHand.empty())
	{
		m_pHand.erase(m_pHand.begin());
	}
	while (!m_pDiscardPile.empty())
	{		
		m_pDiscardPile.erase(m_pDiscardPile.begin());
	}
}

//Play a card and return its value
int Player::PlayOneCard()
{
	if (m_pHand.empty())
	{
	RecycleDiscardPile();
	}
	auto cardPlayed = *m_pHand.begin();
	AddCardToStack(m_pCardsUsed, cardPlayed);
	DisplayCard(cardPlayed);

	m_pHand.erase(m_pHand.begin());

	return (int)cardPlayed->GetValue();
}

	// Play three cards and return value of the third card
int Player::PlayThreeCards()
{
	int cardsToPlay = k_warHandSize;

	//check if player has less than War Hand Size and adjust cardsToPlay.
	if (m_pHand.size() < k_warHandSize)
	{
		if ((m_pHand.size() + m_pDiscardPile.size()) < k_warHandSize)
		{
			RecycleDiscardPile();
			cardsToPlay = ((int)m_pHand.size());
		}
		else if ((m_pHand.size() + m_pDiscardPile.size()) > k_warHandSize)
		{
			RecycleDiscardPile();
		}
		else
		{
			cardsToPlay = ((int)m_pHand.size());
		}
	}

	for (int i = 0; i < cardsToPlay; i++)
	{
		assert(cardsToPlay <= m_pHand.size());
		auto cardPlayed = m_pHand[i];
		AddCardToStack(m_pCardsUsed, cardPlayed);
		DisplayCard(cardPlayed);

	}
	for (int i = 0; i < cardsToPlay; i++)
	{
		m_pHand.erase(m_pHand.begin());
	}
	return (int)(m_pCardsUsed.back()->GetValue());
}

	// Take cards from discard pile shullfe and add to hand
void Player::RecycleDiscardPile()
{
	std::random_device rd;
	std::shuffle(std::begin(m_pDiscardPile), std::end(m_pDiscardPile), rd);

	for (int i = 0; i < (int)m_pDiscardPile.size(); i++)
	{
		auto card = m_pDiscardPile[i];
		AddCardToStack(m_pHand, card);
	}

	while (!m_pDiscardPile.empty())
	{
			m_pDiscardPile.erase(m_pDiscardPile.begin());
	}
}

	// Move cards from one stack to another. 
void Player::AddCardToStack(vector<Card*> pile, Card* card)
{
	if (pile == m_pHand)
	{
		m_pHand.push_back(card);
	}
	else if (pile == m_pCardsUsed)
	{
		m_pCardsUsed.push_back(card);
	}
	else if (pile == m_pDiscardPile)
	{
		m_pDiscardPile.push_back(card);
	}
	else
	{
		cout << "Moving Cards from stack to stack error" << endl;
	}
}

// Take cards won and place at the back of players hand
void Player::TakeCardsWon(Player& loser)
{
	for (int i = 0; i < m_pCardsUsed.size(); i++)
	{
		auto cardPlayed = m_pCardsUsed[i];
		AddCardToStack(m_pDiscardPile, cardPlayed);
	}

	while (!m_pCardsUsed.empty())
	{
		m_pCardsUsed.erase(m_pCardsUsed.begin());		
	}

	for (int i = 0; i < loser.m_pCardsUsed.size(); i++)
	{
		auto cardPlayed = loser.m_pCardsUsed[i];
		AddCardToStack(m_pDiscardPile, cardPlayed);
	}

	while (!loser.m_pCardsUsed.empty())
	{
		loser.m_pCardsUsed.erase(loser.m_pCardsUsed.begin());
	}
}


void Player::ReturnCardsToDeck(vector<Card*> deck)
{
	RecycleDiscardPile();

	for (int i = 0; i < (int)m_pHand.size(); i++)
	{
		auto card = m_pHand[i];
		deck.push_back(card);
	}

	while (!m_pHand.empty())
	{
		m_pHand.erase(m_pHand.begin());
	}

}

void Player::SetCardColor(Card* card)
{
	switch (card->GetSuit())
	{
	case CardSuit::Heart:
	case CardSuit::Diamond:
	{
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console, (int)SuitColor::Red);
		break;
	}
	case CardSuit::Club:
	case CardSuit::Spade:
	{
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console, (int)SuitColor::Black);
		break;
	}	
	default:
		break;
	}
}

void Player::DisplayCard(Card* card)
{
	SetCardColor(card);

	switch (card->GetValue())
	{
	case CardValue::Two:
	{
		cout << "2";
		break;
	}
	case CardValue::Three:
	{
		cout << "3";
		break;
	}
	case CardValue::Four:
	{
		cout << "4";
		break;
	}
	case CardValue::Five:
	{
		cout << "5";
		break;
	}
	case CardValue::Six:
	{
		cout << "6";
		break;
	}
	case CardValue::Seven:
	{
		cout << "7";
		break;
	}
	case CardValue::Eight:
	{
		cout << "8";
		break;
	}
	case CardValue::Nine:
	{
		cout << "9";
		break;
	}
	case CardValue::Ten:
	{
		cout << "10";
		break;
	}
	case CardValue::Jack:
	{
		cout << "J";
		break;
	}
	case CardValue::Queen:
	{
		cout << "Q";
		break;
	}
	case CardValue::King:
	{
		cout << "K";
		break;
	}
	case CardValue::Ace:
	{
		cout << "A";
		break;
	}
	default:
		cout << "$";
		break;
	}

	switch (card->GetSuit())
	{
	case CardSuit::Heart:
	{
		cout << (char)3;
		break;
	}
	case CardSuit::Diamond:
	{
		cout << (char)4;
		break;
	}
	case CardSuit::Club:
	{
		cout << (char)5;
		break;
	}
	case CardSuit::Spade:
	{
		cout << (char)6;
		break;
	}
	default:
		break;
	}

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)SuitColor::Default);
}
