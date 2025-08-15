#pragma once
#include "Component.h"

class Actor;
class _PathFind : public Component
{
public:
	_PathFind(Actor* owner);
	void InitComponent()override;
	void UpdateComponent(float deltaTime)override;
	void RenderComponent(ID2D1RenderTarget* _dxRenderTarget, Vector pos)override;

private:
	void calcPath();

private:
	Actor* _owner = nullptr;
	vector<Cell> _path;
	vector<Cell> _originpath;
	Cell _destCell;
	int8 _checkPathCount = 3;
	int8 _currPathCount = 0;
};