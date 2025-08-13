#include "pch.h"
#include "Door.h"

Door::Door()
{
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

}

void Door::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
}
