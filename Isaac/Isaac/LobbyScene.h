#pragma once
#include "Scene.h"

class LobbyScene : public Scene
{
	using Super = Scene;

public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update(float deltatime) override;
	virtual void Render(ID2D1RenderTarget* _dxRenderTarget) override;

	virtual void loadResources() override;
	virtual void createObjects() override;
	virtual void createUI() override;
	virtual void initTimer() override;
};

