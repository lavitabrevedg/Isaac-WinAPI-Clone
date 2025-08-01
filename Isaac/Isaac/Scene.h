#pragma once
class Scene
{
public:
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

private:
	unordered_set<class Actor*> _actors;
	vector<class Actor*> _renderList[RenderLayer::RL_Count];

	Vector _camerapos;
};

