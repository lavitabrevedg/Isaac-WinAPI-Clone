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
	DirType GetDir() { return _dir; }
	void OnEnterCollision();

	void Open() { _isopen = true; } 
	void Close() { _isopen = false; }
	bool IsOpen() { return _isopen; }

private:
	DirType _dir;
	int32 _roomKey;
	bool _isopen = false;
};

