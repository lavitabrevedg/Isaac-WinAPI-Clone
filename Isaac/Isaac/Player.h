#pragma once
#include "Creature.h"

class Player : public Creature
{
	using Super = Creature;
public:
	Player();
	void Destroy()override;
	void Init(Vector pos)override;

	void Update(float deltatime)override;
	void Render(ID2D1RenderTarget* _dxRenderTarget)override;

	RenderLayer GetRenderLayer() override { return RenderLayer::RL_Player; }
	Vector GetVelocity()override { return _velocity; }

	int32 GetCoins() const { return _coins; }
	int32 GetBooms() const { return _booms; }
	int32 GetKeys() const { return _keys; }

	virtual void OnDamage()override;
	virtual void TakeDamage(float amount)override;
	void Die()override;

private:
	TearStat _playerTearStat;

	class Sprite* _Body = nullptr;

	HeadAndBody _IsaacAnim;
	AnimationController _headAnimCtrl;
	AnimationController _bodyAnimCtrl;

	DirType _currbodyDir;
	DirType _prevbodyDir;
	BodyState _currbodyState;
	BodyState _prevbodyState;

	DirType _currheadDir;

	int32 _coins;
	int32 _keys;
	int32 _booms;

	float nextReadyTime = 0.f;
	float _invulnEndTime = 0.f;
	float now = 0.f;
};

