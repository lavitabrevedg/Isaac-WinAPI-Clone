#include "pch.h"
#include "Block.h"
#include "Texture.h"
#include "Sprite.h"

Block::Block()
{
	_rock = CreateTextureComponent("Rock", 40, 40);

	CreateRectCollider(_rock->GetSize().Width, _rock->GetSize().Height);
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
