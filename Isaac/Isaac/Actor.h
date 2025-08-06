#pragma once
class Component;
class BaseResource;

struct TearStat
{
	float damage;
	float tears;
	float range;
	float shot_speed;
};

class Actor
{
public:
	Actor();
	virtual ~Actor();
	virtual void Init(Vector pos);
	virtual void Destroy();

	virtual void Update(float deltatime);
	virtual void Render(ID2D1RenderTarget* _dxRenderTarget);

	virtual RenderLayer GetRenderLayer() abstract;

	const Vector& GetPos() { return _pos; }
	const Vector& GetCellPos() { return _cellpos; }
	void SetCellpos(float x, float y)
	{
		_cellpos.x = x;
		_cellpos.y = y;
	}

protected:
	class Sprite* CreateSpriteComponent(string spriteName, int32 width = 0, int32 height = 0);
	class Texture* CreateTextureComponent(string bitmapKey, int32 width = 0, int32 height = 0);
	class RectCollider* CreateRectCollider(int32 width, int32 height);

protected:
	vector<Component*> _components;
	Vector _pos;
	Vector _cellpos;
	RECT* _collision;

};

struct AnimationController
{
	int curFrame = 0;
	float timer = 0.f;
	AnimInfo info;
	bool endAnim = true;

	void SetAnim(const AnimInfo& newInfo);
	void Update(float deltatime, Sprite* sprite);
	bool IsEndAnim() { return endAnim; }
};

