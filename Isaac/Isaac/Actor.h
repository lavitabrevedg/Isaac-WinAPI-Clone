#pragma once
class Component;

class Actor
{
public:
	Actor(Vector pos);
	virtual ~Actor();
	virtual void Init();
	virtual void Destroy();

	virtual void Update(float deltatime);
	virtual void Render(ID2D1RenderTarget* _dxRenderTarget);

	const Vector& GetPos() { return _pos; }
	const Vector& GetCellPos() { return _cellpos; }
protected:
	vector<Component*> _components;

	Vector _pos;
	Vector _cellpos;
};

