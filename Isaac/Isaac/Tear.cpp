#include "pch.h"
#include "Tear.h"
#include "Sprite.h"
#include "Texture.h"
#include "PlayScene.h"

Tear::Tear()
{
	
}

void Tear::Destroy()
{
	Super::Destroy();
}

void Tear::Init(Vector pos, DirType dir,TearStat stat, Vector playervelocity)
{
	_tearStat = stat;
	_gravity = 980.f;
	//float limitVel = 70.0f;
	_dirtype = dir;

	Vector dirvalue = dirValue[_dirtype];

	_velocity = dirvalue * _tearStat.shot_speed + playervelocity * 0.91f;

	_zvelocity = 0;
	_z = 50;
	_distance = 0;
	falling = false;

	_sprite = CreateSpriteComponent("Tear", (int)_tearStat.damage * 8, (int)_tearStat.damage * 8);
	CreateRectCollider(_sprite->GetSize().Width, _sprite->GetSize().Height);

	Vector plus = { 20,-20 };
	Super::Init(pos + plus);
}

void Tear::Update(float deltatime)
{
	Super::Update(deltatime);

	if (!falling) {
		Vector pos = _pos + _velocity * deltatime;
		SetPos(pos);
		_distance += _velocity.Length() * deltatime;
		if (_distance >= _tearStat.range) {
			falling = true;
			_zvelocity = 180.f;
		}
	}
	else {
		_zvelocity -= _gravity * deltatime;
		_z += _zvelocity * deltatime;
		Vector pos = _pos + _velocity * deltatime * 0.3f;
		pos.y += 1.f;
		SetPos(pos);
		if (_z <= 0) {
			// ÅÍÁü/»èÁ¦
			PlayScene::GetGameScene()->RemoveTear(this);
		}
	}

	if (_pos.x > GWinSizeX || GWinSizeY < _pos.y || _pos.x < 0 || _pos.y < 0) { PlayScene::GetGameScene()->RemoveTear(this); }
}

void Tear::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	_sprite->SetPos(_pos);
	Super::Render(_dxRenderTarget);
}

