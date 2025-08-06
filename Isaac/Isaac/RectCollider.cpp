#include "pch.h"
#include "RectCollider.h"
#include "Actor.h"
#include "ResourceManager.h"

RectCollider::RectCollider(Actor* actor, float width, float height)
{
	_owner = actor;
	_width = width;
	_height = height;
}

RectCollider::~RectCollider()
{
}

void RectCollider::InitComponent()
{
}

void RectCollider::UpdateComponent(float deltaTime)
{
	_collision.left = (LONG)(_owner->GetPos().x + _width * -0.5f);
	_collision.right = (LONG)(_owner->GetPos().x + _width * 0.5f);
	_collision.top = (LONG)(_owner->GetPos().y + _height * -0.5f);
	_collision.bottom = (LONG)(_owner->GetPos().y + _height * 0.5f);
}

void RectCollider::RenderComponent(ID2D1RenderTarget* _dxRenderTarget, Vector pos)
{
	// 충돌 영역을 그리기
	const D2D1_RECT_F rc = { (float)_collision.left, (float)_collision.top, (float)_collision.right, (float)_collision.bottom };
	_dxRenderTarget->DrawRectangle(rc, ResourceManager::GetInstance()->GetBrush(BrushColor::Red), 1.0, 0);
}
