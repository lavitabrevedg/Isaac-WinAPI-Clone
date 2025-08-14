#pragma once
#include "Actor.h"

class Tear : public Actor
{
	using Super = Actor;
public:
	Tear();
	virtual void Destroy()override;
	virtual void Init(Vector pos, DirType dir, TearStat stat, Vector playervelocity);

	virtual void Update(float deltatime)override;
	virtual void Render(ID2D1RenderTarget* _dxRenderTarget)override;

	virtual RenderLayer GetRenderLayer() override { return RenderLayer::RL_Tear; }

	const TearStat& GetTearstat() { return _tearStat; }
private:
	DirType _dirtype = DirType::DIR_MAX;
	Vector _dir[DirType::DIR_MAX] =
	{
		Vector{-1,0},
		Vector{1,0},
		Vector{0,-1},
		Vector{0,1}
	};
	TearStat _tearStat;

	float _z;
	float _gravity;
	float _zvelocity = {};
	Vector _velocity = {};

	float _distance;
	bool falling;
};

