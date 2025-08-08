#pragma once

#include "Monster.h"

enum MonsterState
{
	MS_IDLE,
	MS_CHASE,
	MS_MAX
};

class ChaseMonster : public Monster
{
	using Super = Monster;
public:
	ChaseMonster();
	virtual ~ChaseMonster();
	virtual void Destroy()override;
	virtual void Init(Vector pos)override;

	virtual void Update(float deltatime)override;
	virtual void Render(ID2D1RenderTarget* _dxRenderTarget)override;

private:
	class Sprite* _sprite = nullptr;
};