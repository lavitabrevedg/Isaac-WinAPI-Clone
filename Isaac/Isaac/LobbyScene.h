#pragma once
#include "Scene.h"

class LobbyScene : public Scene
{
	using Super = Scene;

public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update(float deltatime) override;
	virtual void Render(HDC hdc) override;
};

