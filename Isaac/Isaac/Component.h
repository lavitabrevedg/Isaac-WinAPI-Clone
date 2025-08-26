#pragma once

class Component
{
public:
	virtual ~Component() {}
	virtual void InitComponent() {}
	virtual void UpdateComponent(float deltaTime) {}
	virtual void RenderComponent(ID2D1RenderTarget* _dxRenderTarget) {}

	virtual void SetPos(Vector pos) { _pos = pos; }
	virtual Vector GetPos() { return _pos; }
protected:
	Vector _pos;
};