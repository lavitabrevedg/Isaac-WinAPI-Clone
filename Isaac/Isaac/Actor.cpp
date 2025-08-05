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
	_pos = pos;
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

	_components.emplace_back(sprite);
	return sprite;
}

Texture* Actor::CreateTextureComponent(string bitmapKey, int32 width, int32 height)
{
	Texture* sprite = new Texture(bitmapKey, width, height);
	_components.emplace_back(sprite);
	return sprite;
}

RectCollider* Actor::CreateRectCollider(int32 width, int32 height)
{
	RectCollider* collider = new RectCollider(this, width, height);
	_components.emplace_back(collider);
	_collision = collider->GetCollisionRect();
	return collider;
}