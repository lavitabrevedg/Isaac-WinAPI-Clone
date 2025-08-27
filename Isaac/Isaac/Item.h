#pragma once
#include "Actor.h"

class Item : public Actor
{
	using Super = Actor;

public:
	Item(class ItemData* data);
	void Init(Vector pos);
	void Destroy()override;

	void Update(float deltatime)override;
	void Render(ID2D1RenderTarget* _dxRenderTarget)override;

	RenderLayer GetRenderLayer()override { return RenderLayer::RL_Item; }

	void PickUp(class Player* player);

private:
	class ItemData* _data = nullptr;
	ItemStat _tearstat;
};

