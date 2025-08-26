#pragma once

#include "Component.h"

class RectCollider : public Component
{
public:
	RectCollider(class Actor* owner, float width, float height, Vector offset);
	virtual ~RectCollider();

	void InitComponent() override;
	void UpdateComponent(float deltaTime) override;
	void RenderComponent(ID2D1RenderTarget* _dxRenderTarget) override;

	RECT* GetCollisionRect() { return &_collision; }

	void SetOffset(Vector pos) { _offset = pos; }

private:
	class Actor* _owner = nullptr;
	RECT _collision = {}; // �浹 ����
	float _width = 0; // �ʺ�
	float _height = 0; // ����

	Vector _offset = { 0,0 };
};

