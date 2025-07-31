#include "pch.h"
#include "Room.h"
#include "Player.h"
#include "Tear.h"

void Room::Init()
{
}

void Room::Destroy()
{
}

void Room::Update(float deltatime)
{
}

void Room::Render(HDC hdc)
{
}

void Room::CreateTear(Vector pos, DirType dir)
{
	Tear* tear = new Tear(pos,dir);
}
