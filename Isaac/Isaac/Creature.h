#pragma once
#include "Actor.h"

enum HeadState
{
	H_IDEL,
	H_ATTACK,
	H_MAX
};

enum BodyState
{
	B_IDEL,
	B_WALK,
	B_MAX
};

struct HeadAndBody
{
	AnimInfo _headAnim[HeadState::H_MAX][DirType::DIR_MAX];
	AnimInfo _bodyAnim[BodyState::B_MAX][DirType::DIR_MAX];
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

	virtual Vector GetVelocity() abstract;

	virtual void OnDamage(float amount) abstract;
	virtual void Die() abstract;

protected:
	float _hp;
	float _maxhp;
	Vector _velocity;
	Vector _acceleration;
	float _maxSpeed;
	float _friction;
};
