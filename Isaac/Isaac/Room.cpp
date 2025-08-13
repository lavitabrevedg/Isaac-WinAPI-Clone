#include "pch.h"
#include "Room.h"
#include "Texture.h"
#include "Actor.h"

Room::Room()
{

}

void Room::Init(Vector pos)
{
	worldPos = pos;
	Super::Init(pos);
}

void Room::Destroy()
{
	Super::Destroy();
}

void Room::Update(float deltatime)
{
	Super::Update(deltatime);
}

void Room::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
	_texture->RenderImage(_dxRenderTarget,worldPos);
}
