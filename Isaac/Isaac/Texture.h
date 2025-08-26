#pragma once

#include "BaseResource.h"

class Texture : public BaseResource
{
	using Super = BaseResource;
public:
	Texture(string key, int32 width = 0, int32 height = 0);
	virtual ~Texture();

	void RenderComponent(ID2D1RenderTarget* _dxRenderTarget) override;
	void Render(ID2D1RenderTarget* renderTarget, D2D1_RECT_F src, D2D1_RECT_F dest);

private:
};
