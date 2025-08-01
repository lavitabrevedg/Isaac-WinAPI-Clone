#pragma once
#include "Actor.h"

class Map : public Actor
{
	using Super = Actor;
public:
	Map(Vector pos);

	virtual void Init();
	virtual void Destroy();

	virtual void Update(float deltatime);
	virtual void Render(ID2D1RenderTarget* _dxRenderTarget);

	virtual RenderLayer GetRenderLayer() override { return RenderLayer::RL_Background; }
private:
	class Sprite* _tile = nullptr;
	class Texture* _selector = nullptr;
};

