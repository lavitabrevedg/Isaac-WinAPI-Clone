#pragma once
#include "Scene.h"

class LobbyScene : public Scene
{
	using Super = Scene;

public:
	LobbyScene();
	~LobbyScene();
	void Init() override;
	void Destroy() override;
	void Update(float deltatime) override;
	void Render(ID2D1RenderTarget* _dxRenderTarget) override;

	void loadResources() override;
	void createObjects() override;
	void createUI() override;
	void initTimer() override;
};

