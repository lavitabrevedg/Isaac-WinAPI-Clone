#include "pch.h"
#include "Map.h"

Map::Map()
{
	_selector = CreateTextureComponent("titlemenu", GWinSizeX, GWinSizeY);
}

void Map::Init(Vector pos)
{
	_pos = pos;
	Super::Init(pos);
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
