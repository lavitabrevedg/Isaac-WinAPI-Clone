#pragma once
#include "Actor.h"

enum BlockType
{
	BT_ROCK,
	BT_MAX
};

class Block : public Actor
{
	using Super = Actor;
public:
	Block();

	virtual void Init(Vector pos);
	virtual void Destroy();

	virtual void Update(float deltatime);
	virtual void Render(ID2D1RenderTarget* _dxRenderTarget);

	virtual RenderLayer GetRenderLayer() override { return RenderLayer::RL_Object; }
	
	//BlockType _type[BT_MAX];

	class Texture* _rock = nullptr;
};

