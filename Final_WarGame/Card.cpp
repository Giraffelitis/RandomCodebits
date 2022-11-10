#include "Card.h"

Card::~Card()
{

}

Card::Card(CardSuit suit, CardValue value)
	: m_suit(suit)
	, m_value(value)
	, m_color(SuitColor::Black)
{
	if (m_suit == CardSuit::Club || m_suit == CardSuit::Spade)
	{
		m_color = SuitColor::Black;
	}
	else if (m_suit == CardSuit::Diamond || m_suit == CardSuit::Heart)
	{
		m_color = SuitColor::Red;
	}
	else
	{
		cout << "Suit Value Error" << endl;
	}
}