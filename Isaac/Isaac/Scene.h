#pragma once
class Scene
{
public:
	virtual ~Scene();

	virtual void Init() {};
	virtual void Destroy() {};

	virtual void Update(float deltatime) {};
	virtual void PostUpdate(float deltaTime) {};
	virtual void Render(HDC hdc) {};

	Vector GetCameraPos() { return _camerapos; }

private:
	vector<class Actor*> _actors;
	Vector _camerapos;
};

