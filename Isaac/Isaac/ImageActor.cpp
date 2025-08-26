#include "pch.h"
#include "ImageActor.h"
#include "Sprite.h"
#include "Texture.h"

ImageActor::ImageActor(string spriteName, int32 width, int32 height)
{
	_sprite = CreateSpriteComponent(spriteName,width,height);
}

void ImageActor::Init(Vector pos)
{
	_pos = pos;
}

void ImageActor::Destroy()
{
	Super::Destroy();
}

void ImageActor::Update(float deltatime)
{
	
}

void ImageActor::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	_sprite->SetPos(_pos);
	Super::Render(_dxRenderTarget);
}

