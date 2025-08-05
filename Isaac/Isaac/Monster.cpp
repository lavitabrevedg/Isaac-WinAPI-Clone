#include "pch.h"
#include "Monster.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Destroy()
{
	Super::Destroy();
}

void Monster::Init(Vector pos)
{
	Super::Init(pos);
}

void Monster::Update(float deltatime)
{
	Super::Update(deltatime);
}

void Monster::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
}
