#pragma once
#include "Creature.h"

class Player : public Creature
{
	using Super = Creature;
public:
	Player();
	virtual void Destroy()override;
	virtual void Init(Vector pos)override;

	virtual void Update(float deltatime)override;
	virtual void Render(ID2D1RenderTarget* _dxRenderTarget)override;

	virtual RenderLayer GetRenderLayer() override { return RenderLayer::RL_Player; }
	Vector GetPlayerVelocity()override { return _velocity; }
private:

	TearStat _playerTearStat;

	class Sprite* _Head = nullptr;
	class Sprite* _SideBody = nullptr;
	class Sprite* _Body = nullptr;
};

