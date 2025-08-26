#include "pch.h"
#include "Texture.h"
#include "Game.h"
#include "ResourceManager.h"
#include "DXBitmap.h"

Texture::Texture(string key, int32 width, int32 height) : Super(key, width, height)
{
}

Texture::~Texture()
{
}

void Texture::RenderComponent(ID2D1RenderTarget* _dxRenderTarget)
{
    if (_bitmap->GetBitmap() == nullptr)
        return;

    D2D1_RECT_F srcLeft = D2D1::RectF(
        0,
        0,
        static_cast<float>(_bitmap->GetBitmapSize().Width),
        static_cast<float>(_bitmap->GetBitmapSize().Height));

    D2D1_RECT_F destLeft = D2D1::RectF(
        _pos.x,
        _pos.y,
        _pos.x + static_cast<float>(_size.Width),
        _pos.y + static_cast<float>(_size.Height)
    );
    _dxRenderTarget->DrawBitmap(_bitmap->GetBitmap(), destLeft, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcLeft);
}

void Texture::Render(ID2D1RenderTarget* renderTarget, D2D1_RECT_F src, D2D1_RECT_F dest)
{
    renderTarget->DrawBitmap(_bitmap->GetBitmap(), dest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &src);
}
