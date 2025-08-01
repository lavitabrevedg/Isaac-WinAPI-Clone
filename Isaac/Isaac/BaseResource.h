#pragma once
#include "Component.h"

class DXBitmap;

class BaseResource : public Component
{

public:
	BaseResource(string key, int32 width, int32 height);
	virtual ~BaseResource();

	virtual void UpdateComponent(float deltaTime) {}
	virtual void RenderComponent(ID2D1RenderTarget* renderTarget, Vector pos) {}

	Dimension GetSize() { return _size; }
	void SetBitmapKey(string key, int32 width = 0, int32 height = 0);
	DXBitmap* GetBitmap() { return _bitmap; }

protected:
	DXBitmap* _bitmap = nullptr;
	Dimension		_size = {};
	string		_bitmapKey;
};

