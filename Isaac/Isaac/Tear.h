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

	const DirType GetDir() { return _dirtype; }

	void CleanTear()
	{
		TearStat clean = { 0,0,0,0 };
		_dirtype = DIR_MAX;
		_pos = Vector(-1,-1);
		_tearStat = clean;

		_z = 0.f;
		_zvelocity = 0.f;               // 필요하면 초기 발사 Z속도 설정
		_gravity = 0.f;          // 0이 아니라 기본 중력값
		_distance = 0.f;
		falling = false;
	}
	
private:
	DirType _dirtype = DirType::DIR_MAX;
	TearStat _tearStat;

	float _z;
	float _gravity;
	float _zvelocity = {};
	Vector _velocity = {};

	float _distance;
	bool falling;
};

