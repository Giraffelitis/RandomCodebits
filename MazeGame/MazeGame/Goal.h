#pragma once
#include "PlaceableActor.h"

class Goal : public PlaceableActor
{
public:
	Goal(int x, int y);

	virtual void Draw() override;
	virtual ActorType GetType() override { return ActorType::Goal; }
};