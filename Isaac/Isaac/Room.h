#pragma once

#include "Actor.h"

class Room : public Actor //Room이 actor가 맞나
{
	using Super = Actor;
public:
	Room();

	void Init(Vector pos)override;
	void Destroy()override;

	void Update(float deltatime)override;
	void Render(ID2D1RenderTarget* _dxRenderTarget)override;

	virtual RenderLayer GetRenderLayer() override { return RenderLayer::RL_Room; } //Map이나 ROom도 Rect와 Pos가 있어야함 

	const Vector& GetWorldPos() const { return worldPos; }

	

private:
	Vector worldPos;
	class Texture* _texture = nullptr;
};

