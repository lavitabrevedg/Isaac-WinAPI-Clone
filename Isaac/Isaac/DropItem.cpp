#include "pch.h"
#include "DropItem.h"
#include "Sprite.h"

DropItem::DropItem(string spriteName, int32 width, int32 height)
{
	_sprite = CreateSpriteComponent(spriteName,width,height);
	CreateRectCollider(0,0);
}

void DropItem::Init(Vector pos)
{
	_pos = pos;
	_sprite->SetPos(_pos);
	Super::Init(pos);
}

void DropItem::Destroy()
{
	Super::Destroy();
}

void DropItem::Update(float deltatime)
{
	Super::Update(deltatime);

}

void DropItem::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
}
