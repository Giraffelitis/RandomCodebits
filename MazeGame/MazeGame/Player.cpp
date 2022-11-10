#include "Player.h"
#include <iostream>
#include "Key.h"
#include "AudioManager.h"

using std::cout;

constexpr char kStartingNumberOfLives = 3;

Player::Player()
	: PlaceableActor(0, 0)
	,m_pCurrentKey(nullptr)
	,m_money(0)
	,m_lives(kStartingNumberOfLives)
	,m_HasWater(false)
{

}

bool Player::HasKey()
{
	return m_pCurrentKey != nullptr;
}

bool Player::HasKey(ActorColor color)
{
	return HasKey() && m_pCurrentKey->GetColor() == color;
}

void Player::PickupKey(Key* key)
{
	m_pCurrentKey = key;
}

void Player::UseKey()
{
	m_pCurrentKey->Remove();
	m_pCurrentKey = nullptr;
}

void Player::DropKey()
{
	if (m_pCurrentKey)
	{
		AudioManager::GetInstance()->PlayKeyDropSound();
		m_pCurrentKey->Place(m_pPosition->x, m_pPosition->y);
		m_pCurrentKey = nullptr;
	}
}

void Player::Draw()
{
	cout << "@";
}