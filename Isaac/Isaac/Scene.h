#pragma once

class Actor;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init();
	virtual void Destroy();

	virtual void Update(float deltatime);
	virtual void Render(ID2D1RenderTarget* _dxRenderTarget);

	Vector GetCameraPos() { return _camerapos; }

	virtual void loadResources() abstract;
	virtual void createObjects() abstract;
	virtual void createUI() abstract;
	virtual void initTimer() abstract;

	void RemoveActor(Actor* actor);
	void AddActor(Actor* actor);

	void ReserveRemove(Actor* actor);
	void ReserveAdd(Actor* actor);

protected:
	unordered_set<Actor*> _actors;
	vector<class Actor*> _renderList[RenderLayer::RL_Count];

	unordered_set<Actor*> _reserveAdd;
	unordered_set<Actor*> _reserveRemove;

	Vector _camerapos;
};

