#include "pch.h"
#include "ChaseMonster.h"

ChaseMonster::ChaseMonster()
{
	_hp = 3;
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
}
