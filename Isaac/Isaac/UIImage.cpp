#include "pch.h"
#include "UIImage.h"
#include "Texture.h"
#include "Sprite.h"

UIImage::UIImage(Vector pos, string key, int32 width, int32 height)
{
	CreateTextureComponent(key, width, height);
    Super::Init(pos);
}

UIImage::~UIImage()
{
}


//------------------------------------------------------------------
UISprite::UISprite(Vector pos, string spriteName, int32 width, int32 height) 
{
    _sprite = CreateSpriteComponent(spriteName, width, height);
    Super::Init(pos);
}

UISprite::~UISprite()
{
}

void UISprite::SetIndex(int32 x, int32 y)
{
    if (_sprite)
    {
        _sprite->SetIndex(x, y);
    }
}

//------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
