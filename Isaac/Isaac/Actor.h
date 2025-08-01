#pragma once
class Component;
class BaseResource;

class Actor
{
public:
	Actor(Vector pos);
	virtual ~Actor();
	virtual void Init();
	virtual void Destroy();

	virtual void Update(float deltatime);
	virtual void Render(ID2D1RenderTarget* _dxRenderTarget);

	virtual RenderLayer GetRenderLayer() abstract;

	const Vector& GetPos() { return _pos; }
	const Vector& GetCellPos() { return _cellpos; }

protected:
	class Sprite* CreateSpriteComponent(string spriteName, int32 width, int32 height);
	class Texture* CreateTextureComponent(string bitmapKey, int32 width, int32 height);
	class RectCollider* CreateRectCollider(int32 width, int32 height);

protected:
	vector<Component*> _components;
	Vector _pos;
	Vector _cellpos;
	Sprite* _sprite = nullptr;
	Rect _collision;
};

