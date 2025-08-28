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

		string sprite = _data->_key;

		_sprite = CreateSpriteComponent(sprite, 50, 50);
		CreateRectCollider(50, 50);

		_tearstat = _data->_tearstat;
		_spritekey = _data->_playercostumeKey;
	}
}

void Item::Init(Vector pos)
{
	_pos = pos;
}

void Item::Destroy()
{
	Super::Destroy();
}

void Item::Update(float deltatime)
{
	Super::Update(deltatime);
	Move();
	const RECT* rect = GetCollisionRect();
	Player* player = PlayScene::GetGameScene()->GetPlayer();
	const RECT* rect2 = player->GetCollisionRect();
	if (AABBIntersect(*rect, *rect2))
	{
		PickUp(player);
		PlayScene::GetGameScene()->ReserveRemove(this); 
	}
}

void Item::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	_sprite->SetPos(_pos);
	Super::Render(_dxRenderTarget);
}

void Item::PickUp(Player* player)
{
	player->PickUp(_tearstat,_spritekey);
}

void Item::Move()
{
	float speed = 0.3f;

	if (_movingUp)
	{
		_pos.y -= speed;
		_distance += speed;
		if (_distance >= 20.f)  
		{
			_movingUp = false; 
			_distance = 0.f;
		}
	}
	else
	{
		_pos.y += speed;
		_distance += speed;
		if (_distance >= 20.f) 
		{
			_movingUp = true;
			_distance = 0.f;
		}
	}
}
