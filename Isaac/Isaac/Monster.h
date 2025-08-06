#pragma once
#include "Creature.h"

class Monster : public Creature
{
	using Super = Creature;
public:
	Monster();
	virtual ~Monster();
	virtual void Destroy()override;
	virtual void Init(Vector pos)override;

	virtual void Update(float deltatime)override;
	virtual void Render(ID2D1RenderTarget* _dxRenderTarget)override;

	RenderLayer GetRenderLayer() override { return RenderLayer::RL_Monster; }
	Vector GetPlayerVelocity()override { return _velocity; };

private:
	Actor* Target;
};

