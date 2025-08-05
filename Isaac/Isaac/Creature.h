#pragma once
#include "Actor.h"

enum class State
{
	S_IDLE,
	S_WALK,
	S_ATTACK,
	S_GETUSEITEM,
	S_ONDAMAGE,
	S_MAX
};

class Creature : public Actor
{
	using Super = Actor;
public:
	Creature();
	virtual ~Creature();

	virtual void Init(Vector pos)override;
	virtual void Destroy()override;

	virtual void Update(float deltatime)override;
	virtual void Render(ID2D1RenderTarget* _dxRenderTarget)override;
	virtual RenderLayer GetRenderLayer() abstract;
	virtual Vector GetPlayerVelocity() abstract;

	virtual void TakeDamage(float amount);
	virtual void Die();

protected:
	float _hp;
	float _maxhp;
	Vector _velocity;
	Vector _acceleration;
	float _maxSpeed;
	float _friction;

	DirType _headDir = DirType::DIR_MAX;
	DirType _bodyDir = DirType::DIR_MAX;
	State _currentState = State::S_IDLE;
};
