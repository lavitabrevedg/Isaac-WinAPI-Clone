#include "pch.h"
#include "Map.h"

Map::Map(Vector pos) : Super(pos)
{
	_selector = CreateTextureComponent("titlemenu",480,272);
}

void Map::Init()
{
	Super::Init();
}

void Map::Destroy()
{
	Super::Destroy();
}

void Map::Update(float deltatime)
{
	Super::Update(deltatime);
}

void Map::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
}
