#pragma once
#include "Creature.h"

class Monster : public Creature
{
	using Super = Creature;
public:
	virtual void Destroy()override;
	virtual void Init()override;

	virtual void Update(float deltatime)override;
	virtual void Render(ID2D1RenderTarget* _dxRenderTarget)override;
};

