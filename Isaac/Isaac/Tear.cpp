#include "pch.h"
#include "Tear.h"
#include "Sprite.h"
#include "Texture.h"
#include "PlayScene.h"

Tear::Tear()
{
	_tear = CreateTextureComponent("Tear", 30, 30);
	CreateRectCollider(_tear->GetSize().Width, _tear->GetSize().Height);
}

void Tear::Destroy()
{
	Super::Destroy();
}

void Tear::Init(Vector pos, DirType dir,TearStat stat, Vector playervelocity)
{
	_pos = pos;
	_tearStat = stat;
	_gravity = 980.f;
	_velocity = _dir[dir] * _tearStat.shot_speed + playervelocity * 0.91f;

	_zvelocity = 0;
	_distance = 0;
	falling = false;

	Super::Init(pos);
}

void Tear::Update(float deltatime)
{
	Super::Update(deltatime);

	if (!falling) {
		_pos += _velocity * deltatime;
		_distance += _velocity.Length() * deltatime;
		if (_distance >= _tearStat.range) {
			falling = true;
			_zvelocity = 180.f;
		}
	}
	else {
		_zvelocity -= _gravity * deltatime;
		_z += _zvelocity * deltatime;
		_pos += _velocity * deltatime * 0.3f; //@TODO 구현 안된거같음
		if (_z <= 0) {
			// 터짐/삭제
			PlayScene::GetGameScene()->RemoveTear(this);
		}
	}
}

void Tear::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
}
