#include "pch.h"
#include "Tile.h"
#include "Sprite.h"
#include <fstream>
#include <iostream>
#include <string>

Tile::Tile()
{
}

Tile::Tile(string spriteName, int32 width, int32 height)
{
	_sprite = CreateSpriteComponent(spriteName, width, height);
}

Tile::Tile(Sprite* sprite)
{
	_sprite = sprite;
}

void Tile::Init(Vector pos)
{
	pos = _pos;
}

void Tile::Destroy()
{
	Super::Destroy();
}

void Tile::Update(float deltatime)
{

}

void Tile::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	_sprite->RenderImage(_dxRenderTarget,_pos);
}

void Tile::LoadActor(std::wistringstream& steam)
{
	// 이미 액터가 생성되었다는건 해당 file stream 에서 actorType에 대한 값을 읽은 이후이다.
	wchar_t comma = ',';
	steam >> comma;	// GetActorType() 저장이후 구분자 읽기

	int32 indexX = 0, indexY = 0;
	//steam >> indexX >> comma >> indexY >> comma;

	int32 x = 0, y = 0;
	steam >> x >> comma >> y >> comma;

	int32 w, h;
	steam >> w >> comma >> h >> comma;

	wstring wspriteName;
	std::getline(steam, wspriteName);

	std::string spriteName;
	spriteName.assign(wspriteName.begin(), wspriteName.end());

	_pos = Vector(x, y);
	_sprite = CreateSpriteComponent(spriteName, w, h);
}