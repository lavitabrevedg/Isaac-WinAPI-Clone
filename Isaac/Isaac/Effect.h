#pragma once
#include "Actor.h"

class Effect : public Actor
{
	using Super = Actor;
public:
	Effect(string spriteName, int32 width, int32 height);

	void Init(Vector pos, AnimInfo info);
	void Destroy()override;

	void Update(float deltatime)override;
	void Render(ID2D1RenderTarget* _dxRenderTarget)override;

	RenderLayer GetRenderLayer() { return RenderLayer::RL_Effect; }
private:
	AnimationController _effectAnim;
};

