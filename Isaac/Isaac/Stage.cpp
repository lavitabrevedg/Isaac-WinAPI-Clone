#include "pch.h"
#include "Stage.h"
#include "Room.h"
#include "PlayScene.h"


Stage::Stage()
{
}

void Stage::Init(int32 roomsize)
{
	for (int i = 0; i < roomsize; i++)
	{
		_rooms[i] = new Room();
		_rooms[i]->Init(Vector{ (float)i * (float)GWinSizeX ,0 });
	}
}

void Stage::Destroy()
{
}

void Stage::Update(float deltatime)
{
}

void Stage::Render(ID2D1RenderTarget* _dxRenderTarget)
{
}


