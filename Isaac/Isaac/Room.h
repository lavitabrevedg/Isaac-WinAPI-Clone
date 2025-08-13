#pragma once

#include "Actor.h"

class Room : public Actor //Room�� actor�� �³�
{
	using Super = Actor;
public:
	Room();

	void Init(Vector pos)override;
	void Destroy()override;

	void Update(float deltatime)override;
	void Render(ID2D1RenderTarget* _dxRenderTarget)override;

	virtual RenderLayer GetRenderLayer() override { return RenderLayer::RL_Room; } //Map�̳� ROom�� Rect�� Pos�� �־���� 

	const Vector& GetWorldPos() const { return worldPos; }

	

private:
	Vector worldPos;
	class Texture* _texture = nullptr;
};

