#include "pch.h"
#include "Monster.h"
#include "Sprite.h"
#include "Game.h"
#include "PlayScene.h"

Monster::Monster()
{
	_maxhp = 3;
	_hp = _maxhp;

	_bodyAnim[BodyState::B_IDEL][DirType::DIR_DOWN] = AnimInfo{ 0,0,1,1,true,0.1f };
	_bodyAnim[BodyState::B_IDEL][DirType::DIR_UP] = AnimInfo{ 0,0,1,1,true,0.1f };
	_bodyAnim[BodyState::B_IDEL][DirType::DIR_RIGHT] = AnimInfo{ 0,1,1,1,true,0.1f };
	_bodyAnim[BodyState::B_IDEL][DirType::DIR_LEFT] = AnimInfo{ 0,1,1,1,true,0.1f,true };

	_bodyAnim[BodyState::B_WALK][DirType::DIR_DOWN] = AnimInfo{ 0,0,10,1,true,0.1f };
	_bodyAnim[BodyState::B_WALK][DirType::DIR_UP] = AnimInfo{ 0,0,10,1,true,0.1f };
	_bodyAnim[BodyState::B_WALK][DirType::DIR_RIGHT] = AnimInfo{ 0,1,10,1,true,0.1f };
	_bodyAnim[BodyState::B_WALK][DirType::DIR_LEFT] = AnimInfo{ 0,1,10,1,true,0.1f,true };

	_sprite = CreateSpriteComponent("gaperHead",60,60);
	_Body = CreateSpriteComponent("gaperBody",50,50);

	AnimInfo base = _bodyAnim[BodyState::B_IDEL][DirType::DIR_DOWN];
	_bodyAnimCtrl.SetAnim(base);

	CreateRectCollider(_sprite->GetSize().Width + _Body->GetSize().Width, _sprite->GetSize().Height + _Body->GetSize().Height);
}

Monster::~Monster()
{
}

void Monster::Destroy()
{
	Super::Destroy();
}

void Monster::Init(Vector pos)
{
	Super::Init(pos);
	_maxSpeed = 250.f;
	_friction = 0.95f;
	_velocity = { 0,0 };
	_acceleration = { 0,0 };

	_currbodyDir = DirType::DIR_DOWN;
	_prevbodyDir = DirType::DIR_DOWN;

	_currbodyState = BodyState::B_IDEL;
	_prevbodyState = BodyState::B_IDEL;
}

void Monster::Update(float deltatime)
{
	Super::Update(deltatime);

	if (_currbodyState != _prevbodyState || _currbodyDir != _prevbodyDir) {
		AnimInfo bodyInfo = _bodyAnim[_currbodyState][_currbodyDir];
		_bodyAnimCtrl.SetAnim(bodyInfo);
		_prevbodyState = _currbodyState;
		_prevbodyDir = _currbodyDir;
	}

	_bodyAnimCtrl.Update(deltatime, _Body);
}

void Monster::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	_Body->RenderImage(_dxRenderTarget, _pos + Vector{ 0,14 });
	_sprite->RenderImage(_dxRenderTarget, _pos + Vector{ 0,-14 });
	Super::Render(_dxRenderTarget);
}

void Monster::OnDamage(float amount)
{
	_hp -= amount;
	if (_hp <= 0)
	{
		Die();
	}
}

void Monster::Die()
{
	Game::GetInstance()->GetCurrScene()->ReserveRemove(this);
}
