#include "pch.h"
#include "Player.h"
#include "Game.h"
#include "Scene.h"
#include "InputManager.h"
#include "Tear.h"
#include "PlayScene.h"
#include "Sprite.h"
#include "TimeManager.h"
#include "UIHud.h"
#include "Item.h"
#include "DropItem.h"

Player::Player()
{
	_IsaacAnim._headAnim[HeadState::H_IDEL][DirType::DIR_DOWN] = AnimInfo{ 0,0,1,1,false,0.1f };
	_IsaacAnim._headAnim[HeadState::H_IDEL][DirType::DIR_RIGHT] = AnimInfo{ 2,0,1,1,false,0.1f };
	_IsaacAnim._headAnim[HeadState::H_IDEL][DirType::DIR_UP] = AnimInfo{ 4,0,1,1,false, 0.1f };
	_IsaacAnim._headAnim[HeadState::H_IDEL][DirType::DIR_LEFT] = AnimInfo{ 6,0,1,1,false,0.1f };

	_IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_DOWN] = AnimInfo{ 0,0,2,1,false,0.2f };
	_IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_RIGHT] = AnimInfo{ 2,0,2,1,false,0.2f };
	_IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_UP] = AnimInfo{ 4,0,2,1,false,0.2f };
	_IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_LEFT] = AnimInfo{ 6,0,2,1,false,0.2f };

	_IsaacAnim._bodyAnim[BodyState::B_IDEL][DirType::DIR_DOWN] = AnimInfo{ 0,0,1,1,true,0.1f };
	_IsaacAnim._bodyAnim[BodyState::B_IDEL][DirType::DIR_UP] = AnimInfo{ 0,0,1,1,true,0.1f };
	_IsaacAnim._bodyAnim[BodyState::B_IDEL][DirType::DIR_RIGHT] = AnimInfo{ 0,1,1,1,true,0.1f };
	_IsaacAnim._bodyAnim[BodyState::B_IDEL][DirType::DIR_LEFT] = AnimInfo{ 0,1,1,1,true,0.1f };

	_IsaacAnim._bodyAnim[BodyState::B_WALK][DirType::DIR_DOWN] = AnimInfo{ 1,0,9,1,true,0.1f };
	_IsaacAnim._bodyAnim[BodyState::B_WALK][DirType::DIR_UP] = AnimInfo{ 1,0,9,1,true,0.1f };
	_IsaacAnim._bodyAnim[BodyState::B_WALK][DirType::DIR_RIGHT] = AnimInfo{ 1,1,9,1,true,0.1f };
	_IsaacAnim._bodyAnim[BodyState::B_WALK][DirType::DIR_LEFT] = AnimInfo{ 1,1,9,1,true,0.1f,true };

	_IsaacAnim._actionAnim[A_Hurt] = AnimInfo{ 2,1,1,1,true,2.f };
	_IsaacAnim._actionAnim[A_GetItem] = AnimInfo{ 1,1,1,1,true,2.f };
	_IsaacAnim._actionAnim[A_Die] = AnimInfo{ 3,0,1,1,true,2.f };

	_Body = CreateSpriteComponent("IsaacBody", 50, 35);
	_sprite = CreateSpriteComponent("IsaacHead", 72, 50);
	

	_sprite->SetFrameOffset(0, 0, { 5, 0 });
	_sprite->SetFrameOffset(1, 0, { 5, 0 });
	_sprite->SetFrameOffset(4, 0, { -3,0 });
	_sprite->SetFrameOffset(5, 0, { -3,0 });
	_sprite->SetFrameOffset(6, 0, { -5,0 });
	_sprite->SetFrameOffset(7, 0, { -5,0 });

	_Body->SetFrameOffset(0, 0, { 9, 0 });  
	_Body->SetFrameOffset(1, 0, { 5, 0 });
	_Body->SetFrameOffset(2, 0, { 4, 0 });  
	_Body->SetFrameOffset(3, 0, { 1, 0 });  
	_Body->SetFrameOffset(4, 0, { 0, 0 });  
	_Body->SetFrameOffset(5, 0, { -6, 0 });  
	_Body->SetFrameOffset(6, 0, { -7, 0 });  
	_Body->SetFrameOffset(7, 0, { -8, 0 });  
	_Body->SetFrameOffset(8, 0, { -9, 0 });  
	_Body->SetFrameOffset(9, 0, { -10, 0 });  

	_Body->SetFrameOffset(0, 1, { 9, 0 });
	_Body->SetFrameOffset(1, 1, { 8, 0 });
	_Body->SetFrameOffset(2, 1, { 7, 0 });
	_Body->SetFrameOffset(3, 1, { 6, 0 });
	_Body->SetFrameOffset(4, 1, { 5, 0 });
	_Body->SetFrameOffset(5, 1, { -2, 0 });
	_Body->SetFrameOffset(6, 1, { -3, 0 });
	_Body->SetFrameOffset(7, 1, { -4, 0 });
	_Body->SetFrameOffset(8, 1, { -5, 0 });
	_Body->SetFrameOffset(9, 1, { -6, 0 });

	AnimInfo base = _IsaacAnim._bodyAnim[BodyState::B_IDEL][DirType::DIR_DOWN];
	_bodyAnimCtrl.SetAnim(base);
	base = _IsaacAnim._headAnim[HeadState::H_IDEL][DirType::DIR_DOWN];
	_headAnimCtrl.SetAnim(base);

	CreateRectCollider(_Body->GetSize().Width - 20, _Body->GetSize().Height,Vector(0,10));
}

void Player::Destroy()
{
	Super::Destroy();
}

void Player::Init(Vector pos)
{
	Super::Init(pos);
	_maxhp = 2;
	_hp = _maxhp;
	_maxSpeed = 250.f;
	_friction = 0.95f;
	_velocity = { 0,0 };
	_acceleration = { 0,0 };

	_playerTearStat.damage = 3.5f;
	_playerTearStat.tears = 2.7f;
	_playerTearStat.range = 500.f;
	_playerTearStat.shot_speed = 400.f;

	_currbodyDir = DirType::DIR_DOWN;
	_prevbodyDir = DirType::DIR_DOWN;

	_currbodyState = BodyState::B_IDEL;
	_prevbodyState = BodyState::B_IDEL;

	_coins = 0;
	_booms = 1;
	_keys = 0;
}

void Player::Update(float deltatime)
{
	Super::Update(deltatime);

	float moveForce = 1000.f;
	bool moving = false;

	// Move/Body
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::A)) {
		_acceleration.x -= moveForce; _currbodyDir = DIR_LEFT; moving = true;
	}
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::D)) {
		_acceleration.x += moveForce; _currbodyDir = DIR_RIGHT; moving = true;
	}
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::W)) {
		_acceleration.y -= moveForce; _currbodyDir = DIR_UP; moving = true;
	}
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::S)) {
		_acceleration.y += moveForce; _currbodyDir = DIR_DOWN; moving = true;
	}
	//if (InputManager::GetInstance()->GetButtonDown(KeyType::E))
	//{
	//	PlayScene::GetGameScene()->createObjects
	//}

	if (moving) {
		_currbodyState = B_WALK;
	}
	else {
		_currbodyState = B_IDEL;
		_currbodyDir = DIR_DOWN;
	}

	_currheadDir = _currbodyDir;

	now = TimeManager::GetInstance()->GetNow();
	// Attack/Head
	if (now >= nextReadyTime)
	{
		if (InputManager::GetInstance()->GetButtonPressed(KeyType::Left))
		{
			AnimInfo headInfo = _IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_LEFT];
			_headAnimCtrl.SetAnim(headInfo);
			PlayScene::GetGameScene()->CreateTear(DIR_LEFT, _pos, _playerTearStat, _velocity);
			nextReadyTime = now + 1.f / _playerTearStat.tears;
		}
		else if (InputManager::GetInstance()->GetButtonPressed(KeyType::Right))
		{
			AnimInfo headInfo = _IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_RIGHT];
			_headAnimCtrl.SetAnim(headInfo);
			PlayScene::GetGameScene()->CreateTear(DIR_RIGHT, _pos, _playerTearStat, _velocity);
			nextReadyTime = now + 1.f / _playerTearStat.tears;
		}
		else if (InputManager::GetInstance()->GetButtonPressed(KeyType::Up))
		{
			AnimInfo headInfo = _IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_UP];
			_headAnimCtrl.SetAnim(headInfo);
			PlayScene::GetGameScene()->CreateTear(DIR_UP, _pos, _playerTearStat, _velocity);
			nextReadyTime = now + 1.f / _playerTearStat.tears;
		}
		else if (InputManager::GetInstance()->GetButtonPressed(KeyType::Down))
		{
			AnimInfo headInfo = _IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_DOWN];
			_headAnimCtrl.SetAnim(headInfo);
			PlayScene::GetGameScene()->CreateTear(DIR_DOWN, _pos, _playerTearStat, _velocity);
			nextReadyTime = now + 1.f / _playerTearStat.tears;
		}
	}

	if (_headAnimCtrl.IsEndAnim())
	{
		if (moving)
		{
			AnimInfo headInfo = _IsaacAnim._headAnim[HeadState::H_IDEL][_currheadDir];
			_headAnimCtrl.SetAnim(headInfo);
		}
		else
		{
			AnimInfo headInfo = _IsaacAnim._headAnim[HeadState::H_IDEL][DirType::DIR_DOWN];
			_headAnimCtrl.SetAnim(headInfo);
		}
	}

	if (_currbodyState != _prevbodyState || _currbodyDir != _prevbodyDir) {
		AnimInfo bodyInfo = _IsaacAnim._bodyAnim[_currbodyState][_currbodyDir];
		_bodyAnimCtrl.SetAnim(bodyInfo);
		_prevbodyState = _currbodyState;
		_prevbodyDir = _currbodyDir;
	}

	_bodyAnimCtrl.Update(deltatime, _Body);
	_headAnimCtrl.Update(deltatime, _sprite);
}

void Player::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	float _blinkHz = 10.f;
	bool isInvuln = (now < _invulnEndTime);
	bool blinkOn = ((int)floor(now * _blinkHz) % 2 == 0);
	if (isInvuln && !blinkOn) return;

	_Body->SetPos(_pos + Vector{ 0,13 });
	_sprite->SetPos(_pos + Vector{ 0,-13 });
	Super::Render(_dxRenderTarget);
}

void Player::OnDamage()
{
	PlayScene::GetGameScene()->GetGameHud()->PlayerOnDamage(1);
}

void Player::Die()
{
	Game::GetInstance()->GetCurrScene()->ReserveRemove(this);
	_isDied = true;
}

void Player::PickUp(ItemStat item, string sprite)
{
	_sprite->SetBitmapKey(sprite, 55, 50);

	_sprite->SetFrameOffset(0, 0, { 0, 0 });
	_sprite->SetFrameOffset(1, 0, { 0, 0 });
	_sprite->SetFrameOffset(4, 0, { 0,0 });
	_sprite->SetFrameOffset(5, 0, { 0,0 });
	_sprite->SetFrameOffset(6, 0, { 0,0 });
	_sprite->SetFrameOffset(7, 0, { 0,0 });

	_playerTearStat.damage += item.damageAdd;
	_playerTearStat.damage *= item.damageMul;
	_playerTearStat.tears += item.tearsAdd;
	_playerTearStat.tears *= item.tearsMul;
	_playerTearStat.shot_speed += item.shotspeedAdd;
	_playerTearStat.shot_speed *= item.shotspeedMul;
}

void Player::PickUpDropItem(DorpItem* item)
{
}

void Player::TakeDamage(float amount)
{
	if (now < _invulnEndTime)
		return;

	_hp -= amount;
	OnDamage();

	if (_hp <= 0)
	{
		Die();
	}
	_invulnEndTime = now + 1.0f; //무적시간
}
