#pragma once
#include "PlaceableActor.h" 

class WaterJug : public PlaceableActor
{
public:
	WaterJug(int x, int y, ActorColor color)
		:PlaceableActor(x, y, color)
	{

	}
	virtual void Draw() override;
	virtual ActorType GetType() override { return ActorType::WaterJug; }
};