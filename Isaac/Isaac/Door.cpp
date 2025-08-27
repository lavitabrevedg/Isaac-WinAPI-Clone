#include "pch.h"
#include "Door.h"
#include "Sprite.h"
#include "PlayScene.h"
#include "Game.h"

Door::Door(string spriteName, int32 width, int32 height)
{
	_sprite = CreateSpriteComponent(spriteName, width, height);
	CreateRectCollider(80, 80);
}

Door::Door(Sprite* sprite)
{
	_sprite = sprite;
}

void Door::Init(Vector pos, DirType dir, int32 nextRoomid)
{
	Super::Init(pos);
	_dir = dir;
	_roomKey = nextRoomid;

	switch (_dir)
	{
	case DIR_LEFT:
		_sprite->SetRotate(-90);
		break;
	case DIR_RIGHT:
		_sprite->SetRotate(90);
		break;
	case DIR_UP:
		break;
	case DIR_DOWN:
		_sprite->SetRotate(180);
		break;
	}

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
	_sprite->SetPos(_pos);
	Super::Render(_dxRenderTarget);
}

void Door::OnEnterCollision()
{
	PlayScene::GetGameScene()->LoadRoom(_roomKey);
}