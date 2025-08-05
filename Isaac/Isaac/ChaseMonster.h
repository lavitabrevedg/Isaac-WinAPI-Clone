#pragma once

#include "Monster.h"

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
};