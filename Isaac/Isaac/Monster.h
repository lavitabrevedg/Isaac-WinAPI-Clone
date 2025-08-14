#pragma once
#include "Creature.h"


struct  MonsterID
{
	int type; //13(Fly)
	int variant; //0보통, 1폭발형
	int subtype; // 색 변형/강화된 등
};

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
	virtual ActorType GetActorType() override { return ActorType::AT_Monster; }
	Vector GetVelocity()override { return _velocity; };

	virtual void OnDamage(float amount)override;
	virtual void Die()override;

private:

	class Sprite* _Body = nullptr;

	AnimInfo _bodyAnim[BodyState::B_MAX][DirType::DIR_MAX];

	AnimationController _bodyAnimCtrl;

	DirType _currbodyDir;
	DirType _prevbodyDir;
	BodyState _currbodyState;
	BodyState _prevbodyState;

	Actor* Target;
};

