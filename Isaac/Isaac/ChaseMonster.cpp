#include "pch.h"
#include "ChaseMonster.h"
#include "Sprite.h"
#include "Texture.h"
#include "Sprite.h"

ChaseMonster::ChaseMonster()
{
	_hp = 3;
	_sprite = CreateSpriteComponent("Fly2",30,30);
	CreateRectCollider(_sprite->GetSize().Width, _sprite->GetSize().Height);
}

ChaseMonster::~ChaseMonster()
{
}

void ChaseMonster::Destroy()
{
	Super::Destroy();
}

void ChaseMonster::Init(Vector pos)
{
	Super::Init(pos);
}

void ChaseMonster::Update(float deltatime)
{
	Super::Update(deltatime);
}

void ChaseMonster::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
	_sprite->RenderImage(_dxRenderTarget, _pos);
}
