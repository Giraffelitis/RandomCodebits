#pragma once
#include "PlaceableActor.h"

class Lava : public PlaceableActor
{
public:
	Lava(int x, int y, ActorColor color, ActorColor disabledColor);
	virtual void Draw() override;

	virtual ActorType GetType() override { return ActorType::Lava; }
	bool IsDisabled() { return m_isDisabled; }
	void Disable() { m_isDisabled = true; }

private:
	bool m_isDisabled;
	ActorColor m_disabledColor;
	int m_renderState = 0;
};