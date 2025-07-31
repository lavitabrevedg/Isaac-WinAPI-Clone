#pragma once
#include "Actor.h"

class Block : public Actor
{
	using Super = Actor;
public:
	Block(Vector pos);

	virtual void Init();
	virtual void Destroy();

	virtual void Update(float deltatime);
	virtual void Render(ID2D1RenderTarget* _dxRenderTarget);
};

