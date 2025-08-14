#pragma once
#include "Actor.h"

class Door : public Actor
{
	using Super = Actor;
public:
	Door();

	void Init(Vector pos)override;
	void Destroy()override;
	void Update(float deltatime)override;
	void Render(ID2D1RenderTarget* _dxRenderTarget)override;


	RenderLayer GetRenderLayer() { return RenderLayer::RL_Room; }
	ActorType GetActorType() { return ActorType::AT_Door; }
};

