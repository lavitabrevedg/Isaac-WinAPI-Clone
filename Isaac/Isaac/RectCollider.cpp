#include "pch.h"
#include "RectCollider.h"
#include "Actor.h"
#include "ResourceManager.h"
#include "PlayScene.h"
#include "Game.h"

RectCollider::RectCollider(class Actor* owner, float width, float height, Vector offset)
{
	_owner = owner;
	_width = width;
	_height = height;
	_offset = offset;
}

RectCollider::~RectCollider()
{
}

void RectCollider::InitComponent()
{
}

void RectCollider::UpdateComponent(float deltaTime)
{
	_collision.left = (LONG)((_owner->GetPos().x + _offset.x) + _width * -0.5f);
	_collision.right = (LONG)((_owner->GetPos().x + _offset.x) + _width * 0.5f);
	_collision.top = (LONG)((_owner->GetPos().y + _offset.y) + _height * -0.5f);
	_collision.bottom = (LONG)((_owner->GetPos().y + _offset.y) + _height * 0.5f);
}

void RectCollider::RenderComponent(ID2D1RenderTarget* _dxRenderTarget)
{
	// 충돌 영역을 그리기
	if (Game::GetInstance()->GetCurrScene()->IsRenderGrid())
	{
		const D2D1_RECT_F rc = { (float)_collision.left, (float)_collision.top, (float)_collision.right, (float)_collision.bottom };
		_dxRenderTarget->DrawRectangle(rc, ResourceManager::GetInstance()->GetBrush(BrushColor::Red), 1.0, 0);
	}
}