#pragma once
#include "PlaceableActor.h"

class Teleporter : public PlaceableActor
{
	int m_renderState;
public:
	Teleporter(int x, int y, ActorColor color)
		:PlaceableActor(x, y, color)
	{

	}
	virtual void Draw() override;
	virtual ActorType GetType() override { return ActorType::Teleporter; }
};

