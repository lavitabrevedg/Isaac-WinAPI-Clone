#include "pch.h"
#include "_PathFind.h"

_PathFind::_PathFind(Actor* owner)
{
	_owner = owner;
}

void _PathFind::InitComponent()
{

}

void _PathFind::UpdateComponent(float deltaTime)
{
	if (_owner == nullptr)
		return;
}

void _PathFind::RenderComponent(ID2D1RenderTarget* _dxRenderTarget, Vector pos)
{

}

void _PathFind::calcPath()
{

}
