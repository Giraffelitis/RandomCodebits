#pragma once
#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

enum class SuitColor
{
	Default = 7,
	Black = 240,
	Red = 252
};

enum class CardSuit
{	
	Heart = 3, 
	Diamond,
	Club,
	Spade,

	// Use these to iterate through 
	count = 4,
	begin = 3,
	end = 6
};

enum class CardValue
{
	Two = 2,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
	Ace,

	// Use these to iterate through 
	count = 13,
	begin = 2,
	end = 14
};

class Card
{
public:
	Card(CardSuit m_suit, CardValue m_value);
	~Card();

	CardSuit GetSuit() { return m_suit; }
	CardValue GetValue() { return m_value; }
	SuitColor GetColor() { return m_color; }

protected:
	CardSuit m_suit;
	CardValue m_value;
	SuitColor m_color;
};