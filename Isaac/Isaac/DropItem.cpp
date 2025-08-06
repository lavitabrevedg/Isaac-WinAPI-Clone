#include "pch.h"
#include "DropItem.h"
#include "Sprite.h"

DropItem::DropItem()
{
	_sprite = CreateSpriteComponent("Penny1");
	CreateRectCollider(_sprite->GetSize().Width, _sprite->GetSize().Height);
}

void DropItem::Init(Vector pos)
{
	_pos = pos;
	Super::Init(pos);
}

void DropItem::Destroy()
{
	SAFE_DELETE(_sprite);
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
