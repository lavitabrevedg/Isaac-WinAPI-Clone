#pragma once
#include "Actor.h"

class Door : public Actor
{
	using Super = Actor;
public:
	Door(string spriteName, int32 width, int32 height);
	Door(Sprite* sprite);

	void Init(Vector pos, DirType dir,int32 nextRoomid);
	void Destroy()override;
	void Update(float deltatime)override;
	void Render(ID2D1RenderTarget* _dxRenderTarget)override;

	RenderLayer GetRenderLayer() { return RenderLayer::RL_Object; }
	ActorType GetActorType() { return ActorType::AT_Door; }
	void OnEnterCollision();

	void OpenClosed(bool b) { _isopen = !_isopen; } //¾Ë¾Æ¼­ ¹Ù²ã³ö

private:
	DirType _dir;
	int32 _roomKey;
	bool _isopen = false;
};

