#pragma once

#include "Component.h"

class RectCollider : public Component
{
public:
	RectCollider(class Actor* owner, float width, float height);
	virtual ~RectCollider();

	void InitComponent() override;
	void UpdateComponent(float deltaTime) override;
	void RenderComponent(ID2D1RenderTarget* _dxRenderTarget,Vector pos) override;

	RECT* GetCollisionRect() { return &_collision; }

private:
	class Actor* _owner = nullptr;
	RECT _collision = {}; // �浹 ����
	float _width = 0; // �ʺ�
	float _height = 0; // ����
};

