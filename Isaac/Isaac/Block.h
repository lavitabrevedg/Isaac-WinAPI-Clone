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
	Block(string spriteName, int32 width, int32 height);

	void Init(Vector pos)override;
	void Destroy()override;

	void Update(float deltatime)override;
	void Render(ID2D1RenderTarget* _dxRenderTarget)override;

	RenderLayer GetRenderLayer() override { return RenderLayer::RL_Object; }
	ActorType GetActorType() override { return ActorType::AT_Block; }
	
	//BlockType _type[BT_MAX];

};

