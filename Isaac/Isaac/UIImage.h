#pragma once
#include "UIWidget.h"

class Texture;
class Sprite;

class UIImage: public UIWidget
{
	using Super = UIWidget;

public:
	UIImage(Vector pos, string key, int32 width = 0, int32 height = 0);
	virtual ~UIImage();

private:
};

class UISprite : public UIWidget
{
	using Super = UIWidget;

public:
	UISprite(Vector pos, string spriteName, int32 width = 0, int32 height = 0);
	virtual ~UISprite();

	void SetIndex(int32 x, int32 y);

private:
	Sprite* _sprite = nullptr;
};