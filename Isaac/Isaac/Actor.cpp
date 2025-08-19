#include "pch.h"
#include "Actor.h"
#include "RectCollider.h"
#include "Scene.h"
#include "Game.h"
#include "PlayScene.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Texture.h"
#include <fstream>
#include <iostream>
#include <string>

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

	for (auto iter : _sprites)
	{
		SAFE_DELETE(iter);
	}
	_sprites.clear();
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
	sprite->SetSpriteName(spriteName);
	_sprites.push_back(sprite);

	return sprite;
}

Texture* Actor::CreateTextureComponent(string bitmapKey, int32 width, int32 height)
{
	Texture* sprite = new Texture(bitmapKey, width, height);

	return sprite;
}

RectCollider* Actor::CreateRectCollider(int32 width, int32 height)
{
	RectCollider* collider = new RectCollider(this, (float)width, (float)height);
	_components.emplace_back(collider);
	_collision = collider->GetCollisionRect();
	return collider;
}

void AnimationController::SetAnim(const AnimInfo& newInfo)
{
	info = newInfo;
	curFrameX = info.startX;
	curFrameY = info.startY;
	timer = 0.f;
	_isEnd = false;
}

void AnimationController::Update(float deltatime, Sprite* sprite)
{
	timer += deltatime;
	if (timer > info.duration && !_isEnd)
	{
		timer -= info.duration;
		curFrameX = (curFrameX + 1) % info.countX;

		sprite->SetIndex(info.startX + curFrameX, curFrameY);
		sprite->SetFlip(info.flipX);
		if (curFrameX == 0)
		{
			if (info.countY != 0) { curFrameY++;}
			if (curFrameY = info.countY)
			{
				if (info.loop == true) { curFrameX = info.startX; curFrameY = info.startY; }
				else { _isEnd = true; }
			}
		}
	}
}

void Actor::SetPos(Vector newPos)
{
	Vector prevPos = _pos;
	_pos = newPos;

	// �׸��带 ������Ʈ
	// Scene�� �˷��ش�.
	Game::GetInstance()->GetCurrScene()->UpdateGrid(this, prevPos, newPos);
}

void Actor::SaveActor(std::wofstream& file)
{
	Sprite* sprite = GetSprite();
	if (nullptr == sprite)
		return;

	int32 indexX = 0, indexY = 0;
	sprite->GetIndex(indexX, indexY);

	Vector pos = GetPos();
	char comma = ','; // ������ ������ ������ ����
	// cout <<
	// cin >> 
	file << (int32)GetActorType() << comma;	// 1��°�� ���� Ÿ�� ����
	//file << indexX << comma << indexY << comma;	// 2��° Sprite
	file << (int32)pos.x << comma << (int32)pos.y << comma; // 3��° ��ǥ
	file << sprite->GetSize().Width << comma << sprite->GetSize().Height << comma;

	// �������� spriteName
	file << sprite->GetSpriteName().c_str();
	file << std::endl;
}

void Actor::LoadActor(std::wistringstream& steam)
{
	if (!_sprite)
		return;

	// �̹� ���Ͱ� �����Ǿ��ٴ°� �ش� file stream ���� actorType�� ���� ���� ���� �����̴�.
	wchar_t comma = ',';
	steam >> comma;	// GetActorType() �������� ������ �б�

	int32 indexX = 0, indexY = 0;
	//steam >> indexX >> comma >> indexY >> comma;

	int32 x = 0, y = 0;
	steam >> x >> comma >> y >> comma;

	int32 w, h;
	steam >> w >> comma >> h >> comma;

	wstring wspriteName;
	std::getline(steam, wspriteName);
	
	std::string spriteName;
	spriteName.assign(wspriteName.begin(), wspriteName.end());

	Init(Vector((float)x, (float)y));
	_sprite->SetIndex(indexX, indexY);
	_sprite->SetSpriteName(spriteName);
}
