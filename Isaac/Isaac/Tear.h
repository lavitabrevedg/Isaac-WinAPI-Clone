#pragma once
#include "Actor.h"

class Tear : public Actor
{
	using Super = Actor;
public:
	Tear(Vector pos, DirType dir);
	virtual void Destroy()override;
	virtual void Init()override;

	virtual void Update(float deltatime)override;
	virtual void Render(ID2D1RenderTarget* _dxRenderTarget)override;

	virtual RenderLayer GetRenderLayer() override { return RenderLayer::RL_Tear; }

private:
};

