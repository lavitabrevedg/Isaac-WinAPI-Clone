#pragma once
#include "Actor.h"

class Tile : public Actor
{
	using Super = Actor;
public:
	Tile();
	Tile(string spriteName, int32 width, int32 height);
	Tile(class Sprite* sprite);

	void Init(Vector pos)override;

	void Destroy()override;
	void Update(float deltatime)override;
	void Render(ID2D1RenderTarget* _dxRenderTarget)override;

	RenderLayer GetRenderLayer()override { return RenderLayer::RL_Room; }
	ActorType GetActorType()override { return ActorType::AT_Tile; }
	virtual void LoadActor(std::wistringstream& steam) override;
};

