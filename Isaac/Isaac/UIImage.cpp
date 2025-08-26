#include "pch.h"
#include "UIImage.h"
#include "Texture.h"
#include "Sprite.h"

UIImage::UIImage(Vector pos, string key, int32 width, int32 height)
{
	CreateTextureComponent(pos,key, width, height);
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
    _sprite->SetPos(pos);
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

void UISprite::GetIndex(int32 &Outx, int32 &Outy)
{
    if (_sprite)
    {
        _sprite->GetIndex(Outx, Outy);
    }
}

//------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
