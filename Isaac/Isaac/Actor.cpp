#include "pch.h"
#include "Actor.h"
#include "RectCollider.h"

Actor::Actor(Vector pos) : _pos(pos)
{
}

Actor::~Actor()
{
}

void Actor::Init()
{

}

void Actor::Destroy()
{
	for (auto iter : _components)
	{
		SAFE_DELETE(iter);
	}
	_components.clear();

}

void Actor::Update(float deltatime)
{
	for (auto iter : _components)
	{
		iter->UpdateComponent(deltatime);
	}
}

void Actor::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	for (auto iter : _components)
	{
		iter->RenderComponent(_dxRenderTarget,_pos);
	}
}