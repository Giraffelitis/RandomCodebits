#pragma once
#include "PlaceableActor.h"

class Money : public PlaceableActor
{
public:
	Money(int x, int y, int worth);

	int GetWorth() const { return m_worth; }

	virtual void Draw() override;
	virtual ActorType GetType() override { return ActorType::Money; }

private:
	int m_worth;
};