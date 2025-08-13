#include "pch.h"
#include "Block.h"
#include "Texture.h"
#include "Sprite.h"

Block::Block(string spriteName, int32 width, int32 height)
{
	_sprite = CreateSpriteComponent(spriteName, width, height);

	CreateRectCollider(_sprite->GetSize().Width, _sprite->GetSize().Height);

	_sprites.push_back(_sprite);
}

void Block::Init(Vector pos)
{
	_pos = pos;
	Super::Init(pos);
}

void Block::Destroy()
{
	Super::Destroy();
}

void Block::Update(float deltatime)
{
	Super::Update(deltatime);
}

void Block::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
}
