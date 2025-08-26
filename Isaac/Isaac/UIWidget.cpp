#include "pch.h"
#include "UIWidget.h"
#include "Sprite.h"

UIWidget::UIWidget()
{
}

UIWidget::~UIWidget()
{
	Destroy();
}

void UIWidget::Init(Vector pos)
{
	_pos = pos;
}

void UIWidget::Update(float deltaTime)
{
	if (false == _visible)
		return;

	Super::Update(deltaTime);
}

void UIWidget::Render(ID2D1RenderTarget* renderTarget)
{
	if (false == _visible)
		return;

	Super::Render(renderTarget);
}
