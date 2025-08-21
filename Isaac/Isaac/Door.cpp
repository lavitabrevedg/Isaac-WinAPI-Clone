#include "pch.h"
#include "Door.h"
#include "Sprite.h"

Door::Door(string spriteName, int32 width, int32 height)
{
	_sprite = CreateSpriteComponent(spriteName, width, height);
	CreateRectCollider(0,0);

	_sprite->SetRotate(_dir * 90);
}

Door::Door(Sprite* sprite)
{
	_sprite = sprite;
}

void Door::Init(Vector pos)
{
	Super::Init(pos);
}

void Door::Destroy()
{
	Super::Destroy();
}

void Door::Update(float deltatime)
{
	Super::Update(deltatime);
}

void Door::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
	_sprite->RenderImage(_dxRenderTarget, _pos);
}

void OnEnterCollision(RectCollider* other)
{

}