#pragma once
#include "UIBase.h"

class UISprite;

class UITitle : public UIBase
{
	using Super = UIBase;
public:
	UITitle();
	virtual ~UITitle();

	void Init() override;
	void Update(float deltaTime) override;
	void Render(ID2D1RenderTarget* renderTarget) override;

private:
    UISprite* _titles;
	struct AnimationController* _anim;
};