#pragma once
#include "PlaceableActor.h"

class Key;

class Player : public PlaceableActor
{
public:
	Player();

	bool HasKey();
	bool HasKey(ActorColor color);
	void PickupKey(Key* key);
	void UseKey();
	void DropKey();
	bool HasWater() { return m_HasWater; }
	void PickupWater() { m_HasWater = true; }
	void UseWater() { m_HasWater = false; }
	Key* GetKey() { return m_pCurrentKey; }

	void AddMoney(int money) { m_money += money; }
	int GetMoney() { return m_money; }

	int GetLives() { return m_lives; }
	void DecrementLives(int damage) { m_lives = m_lives - damage; }
	void KillPlayer() { m_lives = -1; }

	virtual void Draw() override;
	virtual ActorType GetType() override { return ActorType::Player; }

private:
	Key* m_pCurrentKey;
	int m_money;
	int m_lives;
	bool m_HasWater;
};