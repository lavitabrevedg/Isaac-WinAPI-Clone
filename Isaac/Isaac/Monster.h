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

	virtual void OnDamage()override;
	virtual void TakeDamage(float amount)override;
	virtual void TakeDamage(float amount, DirType dir)override;
	virtual void Die()override;

private:

	class Sprite* _Body = nullptr;

	AnimInfo _bodyAnim[BodyState::B_MAX][DirType::DIR_MAX];

	AnimationController _bodyAnimCtrl;

	DirType _currbodyDir;
	DirType _prevbodyDir;

	Actor* Target;

	vector<Cell> _path;
	int8 _checkCount = 30;
	int8 _currCount = 0;
	int _pathIdx = 0;
	float _arrive = 5.0f;

	float _attacedTime;
	float now;

	void UpdateFacingFromDir(const Vector& dir) {
		if (fabs(dir.x) > fabs(dir.y)) _currbodyDir = (dir.x >= 0) ? DirType::DIR_RIGHT : DirType::DIR_LEFT;
		else                            _currbodyDir = (dir.y >= 0) ? DirType::DIR_DOWN : DirType::DIR_UP;
	}
};

