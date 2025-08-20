#include "pch.h"
#include "Player.h"
#include "Game.h"
#include "Scene.h"
#include "InputManager.h"
#include "Tear.h"
#include "PlayScene.h"
#include "Sprite.h"


Player::Player()
{
	_maxhp = 3;
	_hp = _maxhp;

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

	_Head = CreateSpriteComponent("IsaacHead", 72, 50);
	_Body = CreateSpriteComponent("IsaacBody", 50, 35);


	_Head->SetFrameOffset(0, 0, { 5, 0 });
	_Head->SetFrameOffset(1, 0, { 5, 0 });
	_Head->SetFrameOffset(4, 0, { -3,0 });
	_Head->SetFrameOffset(5, 0, { -3,0 });
	_Head->SetFrameOffset(6, 0, { -5,0 });
	_Head->SetFrameOffset(7, 0, { -5,0 });


	_Body->SetFrameOffset(0, 0, { 9, 0 });  
	_Body->SetFrameOffset(1, 0, { 7, 0 });
	_Body->SetFrameOffset(2, 0, { 6, 0 });  
	_Body->SetFrameOffset(3, 0, { 5, 0 });  
	_Body->SetFrameOffset(4, 0, { 4, 0 });  
	_Body->SetFrameOffset(5, 0, { -3, 0 });  
	_Body->SetFrameOffset(6, 0, { -4, 0 });  
	_Body->SetFrameOffset(7, 0, { -5, 0 });  
	_Body->SetFrameOffset(8, 0, { -6, 0 });  
	_Body->SetFrameOffset(9, 0, { -7, 0 });  

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

	CreateRectCollider(_Head->GetSize().Width - 10, _Head->GetSize().Height + _Body->GetSize().Height - 10);
}

void Player::Destroy()
{
	Super::Destroy();
}

void Player::Init(Vector pos)
{
	Super::Init(pos);
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

	if (moving) {
		_currbodyState = B_WALK;
	}
	else {
		_currbodyState = B_IDEL;
		_currbodyDir = DIR_DOWN;
	}

	_currheadDir = _currbodyDir;

	// Attack/Head
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::Left))
	{
		AnimInfo headInfo = _IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_LEFT];
		_headAnimCtrl.SetAnim(headInfo);
		PlayScene::GetGameScene()->CreateTear(DIR_LEFT, _pos, _playerTearStat, _velocity);
	}
	else if (InputManager::GetInstance()->GetButtonPressed(KeyType::Right))
	{
		AnimInfo headInfo = _IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_RIGHT];
		_headAnimCtrl.SetAnim(headInfo);
		PlayScene::GetGameScene()->CreateTear(DIR_RIGHT, _pos, _playerTearStat, _velocity);
	}
	else if (InputManager::GetInstance()->GetButtonPressed(KeyType::Up))
	{
		AnimInfo headInfo = _IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_UP];
		_headAnimCtrl.SetAnim(headInfo);
		PlayScene::GetGameScene()->CreateTear(DIR_UP, _pos, _playerTearStat, _velocity);
	}
	else if (InputManager::GetInstance()->GetButtonPressed(KeyType::Down))
	{
		AnimInfo headInfo = _IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_DOWN];
		_headAnimCtrl.SetAnim(headInfo);
		PlayScene::GetGameScene()->CreateTear(DIR_DOWN, _pos, _playerTearStat, _velocity);
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
	_headAnimCtrl.Update(deltatime, _Head);
}

void Player::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	_Body->RenderImage(_dxRenderTarget, _pos + Vector{ 0,13 });
	_Head->RenderImage(_dxRenderTarget, _pos + Vector{ 0,-13 });
	Super::Render(_dxRenderTarget);
}

void Player::OnDamage()
{
}

void Player::Die()
{
	Game::GetInstance()->GetCurrScene()->ReserveRemove(this);
}

void Player::TakeDamage(float amount)
{
	_hp -= amount;
	OnDamage();
	if (_hp <= 0)
	{
		Die();
	}
}
