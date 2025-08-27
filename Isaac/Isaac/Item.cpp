#include "pch.h"
#include "Item.h"
#include "ItemData.h"
#include "Sprite.h"
#include "Player.h"
#include "PlayScene.h"

Item::Item(ItemData* data)
{
	if (data != nullptr)
	{
		//_data = new ItemData();
		_data = data;
	}
	string sprite = _data->_key;

	_sprite = CreateSpriteComponent(sprite, 50, 50);
	CreateRectCollider(50,50);

	_tearstat = _data->_tearstat;
}

void Item::Init(Vector pos)
{
	Super::Init(pos);
	_pos = pos;
	_sprite->SetPos(_pos);
}

void Item::Destroy()
{
	Super::Destroy();
}

void Item::Update(float deltatime)
{
	Super::Update(deltatime);

	const RECT* rect = GetCollisionRect();
	Player* player = PlayScene::GetGameScene()->GetPlayer();
	const RECT* rect2 = player->GetCollisionRect();
	if (AABBIntersect(*rect, *rect2));
	{
		PickUp(player);
		PlayScene::GetGameScene()->ReserveRemove(this); //@TODO 적용은 되는데 템이 갑자기 사라진다.
	}
}

void Item::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
}

void Item::PickUp(Player* player)
{
	player->PickUp(_tearstat);
}
