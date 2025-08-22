#pragma once
class Component;
class BaseResource;
class Sprite;

enum ActorType : int8
{
	AT_Tile,
	AT_Monster,
	AT_Block,
	AT_Door,
	AT_Count,
};

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
	virtual ActorType GetActorType() { return ActorType::AT_Count; }

	const Vector& GetPos() { return _pos; }
	Sprite* GetSprite() { return _sprite; }
	const RECT* GetCollisionRect() const { return _collision; }

	virtual void SetPos(Vector newPos);

	virtual void SaveActor(std::wofstream& file);
	virtual void LoadActor(std::wistringstream& steam);

	virtual void OnDamage() {};
	virtual void TakeDamage(float amount) {};
	virtual void TakeDamage(float amount,DirType dir) {}; //@TODO OnEnterCollision을 만들어야하나
protected:
	class Sprite* CreateSpriteComponent(string spriteName, int32 width = 0, int32 height = 0);
	class Texture* CreateTextureComponent(string bitmapKey, int32 width = 0, int32 height = 0);
	class RectCollider* CreateRectCollider(int32 width, int32 height,Vector offset = {0,0});

protected:
	vector<Component*> _components; //@TODO std::Map으로 만들어서 COmponent가 pos를 갖고있어서 그리거나 업데이트 할때 내가 지정한 pos대로 그리고 업데이트하면 좋을것 같은데
	vector<Sprite*> _sprites;
	Vector _pos;
	RECT* _collision;

	Sprite* _sprite;
};

struct AnimationController
{
private:
	int curFrameX;
	int curFrameY;
	float timer;
	AnimInfo info;
	bool _isEnd;

public:
	void SetAnim(const AnimInfo& newInfo);
	void Update(float deltatime, Sprite* sprite);
	bool IsEndAnim() { return _isEnd; }
};

