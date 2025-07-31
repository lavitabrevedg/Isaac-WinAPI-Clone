#pragma once
#include "Scene.h"

class Stage_Scene : public Scene
{
	using Super = Scene;

public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update(float deltatime) override;
	virtual void Render(HDC hdc) override;
};

