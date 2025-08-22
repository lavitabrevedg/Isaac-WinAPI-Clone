#pragma once
#include "Actor.h"

class UIWidget : public Actor
{
	using Super = Actor;
public:
	UIWidget();
	virtual ~UIWidget();

	void Init(Vector pos)override;
	void Update(float deltatime)override;
	void Render(ID2D1RenderTarget* _dxRenderTarget)override;

	virtual RenderLayer GetRenderLayer() override { return RenderLayer::RL_UI; }

	bool GetVisible() const { return _visible; }
	void SetVisible(bool visible) { _visible = visible; }
private:
	bool _visible = true;
};
