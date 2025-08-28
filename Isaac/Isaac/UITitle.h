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

	UIImage* _gameName;
	
	bool _movingUp = true;
	float _distance = 0;
	Vector _namepos = { GWinSizeX / 2, 130 };
};