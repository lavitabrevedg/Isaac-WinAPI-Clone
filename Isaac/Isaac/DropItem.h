#pragma once
#include "Actor.h"

class DropItem : public Actor
{
	using Super = Actor;
public:
	DropItem();
	void Init(Vector pos)override;
	void Destroy()override;

	void Update(float deltatime)override;
	void Render(ID2D1RenderTarget* _dxRenderTarget)override;

	RenderLayer GetRenderLayer()override { return RenderLayer::RL_Item; }

private:
};

