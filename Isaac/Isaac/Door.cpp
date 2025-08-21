#include "pch.h"
#include "Door.h"
#include "Sprite.h"
#include "PlayScene.h"
#include "Game.h"

Door::Door(string spriteName, int32 width, int32 height)
{
	_sprite = CreateSpriteComponent(spriteName, width, height);
	CreateRectCollider(0,0);
}

Door::Door(Sprite* sprite)
{
	_sprite = sprite;
}

void Door::Init(Vector pos, DirType dir, int32 nextRoomid)
{
	Super::Init(pos);
	_dir = dir;
	_sprite->SetRotate(dir * 90.f);
	_roomKey = nextRoomid;
}

void Door::Destroy()
{
	Super::Destroy();
}

void Door::Update(float deltatime)
{
	Super::Update(deltatime);

	if (!_isopen)
	{
		_sprite->SetIndex(1, 0);
	}
	else
	{
		_sprite->SetIndex(0, 0);
	}
}

void Door::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
	_sprite->RenderImage(_dxRenderTarget, _pos);
}

void Door::OnEnterCollision()
{
	if (_isopen)
	{
		PlayScene::GetGameScene()->LoadRoom(_roomKey);
	}
}