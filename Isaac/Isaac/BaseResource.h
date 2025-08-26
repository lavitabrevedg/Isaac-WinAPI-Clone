#pragma once
#include "Component.h"

class DXBitmap;

class BaseResource : public Component //@TODO Compomnent를 상속받고 _pos 멤버 변수를 추가하자 그리고 actor에서 render돌때 pos는 getpos해서 그 위치에 그리도록
{

public:
	BaseResource(string key, int32 width, int32 height);
	virtual ~BaseResource();

	virtual void UpdateComponent(float deltaTime) {}
	virtual void RenderComponent(ID2D1RenderTarget* renderTarget) {}

	Dimension GetSize() { return _size; }
	void SetBitmapKey(string key, int32 width = 0, int32 height = 0);
	DXBitmap* GetBitmap() { return _bitmap; }

protected:
	DXBitmap* _bitmap = nullptr;
	Dimension		_size = {};
	string		_bitmapKey;
};

