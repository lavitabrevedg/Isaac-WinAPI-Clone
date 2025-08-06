#pragma once
#include "Creature.h"

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
	Vector GetPlayerVelocity()override { return _velocity; }
private:

	TearStat _playerTearStat;

	class Sprite* _Head = nullptr;
	class Sprite* _Body = nullptr;

	struct HeadAndBody
	{
		AnimInfo _headAnim[HeadState::H_MAX][DirType::DIR_MAX];
		AnimInfo _bodyAnim[BodyState::B_MAX][DirType::DIR_MAX];
	};

	HeadAndBody _IsaacAnim;
	AnimationController _headAnimCtrl;
	AnimationController _bodyAnimCtrl;

	DirType _currbodyDir;
	DirType _prevbodyDir;
	BodyState _currbodyState;
	BodyState _prevbodyState;

	DirType _headDir;
};

