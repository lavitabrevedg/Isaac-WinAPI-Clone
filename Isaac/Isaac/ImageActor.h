#pragma once
#include "Actor.h"
class ImageActor : public Actor
{
	using Super = Actor;

public:
	ImageActor(string spriteName, int32 width, int32 height);

	void Init(Vector pos)override;
	void Destroy()override;

	void Update(float deltatime)override;
	void Render(ID2D1RenderTarget* _dxRenderTarget)override;

	virtual RenderLayer GetRenderLayer() override { return RenderLayer::RL_Image; }
private:
	Sprite* _sprite = nullptr;
};

