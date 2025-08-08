#include "pch.h"
#include "Actor.h"
#include "RectCollider.h"
#include "Scene.h"
#include "Game.h"
#include "PlayScene.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Texture.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::Init(Vector pos)
{
	Game::GetInstance()->GetCurrScene()->UpdateGrid(this, Vector(-1, -1), pos);
	SetPos(pos);
}

void Actor::Destroy()
{
	for (auto iter : _components)
	{
		SAFE_DELETE(iter);
	}
	_components.clear();

}

void Actor::Update(float deltatime)
{
	for (auto iter : _components)
	{
		iter->UpdateComponent(deltatime);
	}
}

void Actor::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	for (auto iter : _components)
	{
		iter->RenderComponent(_dxRenderTarget,_pos);
	}
}

Sprite* Actor::CreateSpriteComponent(string spriteName, int32 width, int32 height)
{
	const SpriteInfo* info = ResourceManager::GetInstance()->GetSpriteInfo(spriteName);
	if (nullptr == info)
		return nullptr;

	Sprite* sprite = new Sprite(info->bitmapKey, width, height, info->alignCenter);
	sprite->SetIndex(info->indexX, info->indexY);
	sprite->SetApplyCamera(GetRenderLayer() != RenderLayer::RL_UI);

	return sprite;
}

Texture* Actor::CreateTextureComponent(string bitmapKey, int32 width, int32 height)
{
	Texture* sprite = new Texture(bitmapKey, width, height);

	return sprite;
}

RectCollider* Actor::CreateRectCollider(int32 width, int32 height)
{
	RectCollider* collider = new RectCollider(this, width, height);
	_components.emplace_back(collider);
	_collision = collider->GetCollisionRect();
	return collider;
}

void AnimationController::SetAnim(const AnimInfo& newInfo)
{
	info = newInfo;
	curFrame = 0;
	timer = 0.f;
	endAnim = false;
}

void AnimationController::Update(float deltatime, Sprite* sprite)
{
	timer += deltatime;
	if (timer > info.durtaion)
	{
		timer -= info.durtaion;
		curFrame = (curFrame + 1) % info.countX;
		sprite->SetIndex(info.startX + curFrame, info.startY);
		sprite->SetFlip(info.flipX);
		if (curFrame == 0)
			endAnim = true;
	}
}

void Actor::SetPos(Vector newPos)
{
	Vector prevPos = _pos;
	_pos = newPos;

	// 그리드를 업데이트
	// Scene에 알려준다.
	Game::GetInstance()->GetCurrScene()->UpdateGrid(this, prevPos, newPos);
}