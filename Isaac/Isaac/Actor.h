#pragma once
class Component;

class Actor
{
public:
	Actor(Vector pos);
	virtual ~Actor();
	virtual void Destroy();
	virtual void Init();

	virtual void Update(float deltatime);
	virtual void Render(HDC hdc);

	const Vector& GetPos() { return _pos; }
private:
	vector<Component> _components;
	Vector _pos;
};

