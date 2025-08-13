#include "pch.h"
#include "Player.h"
#include "Game.h"
#include "Scene.h"
#include "InputManager.h"
#include "Tear.h"
#include "Room.h"
#include "PlayScene.h"
#include "Sprite.h"


Player::Player()
{
	_maxhp = 3;
	_hp = _maxhp;

	_IsaacAnim._headAnim[HeadState::H_IDEL][DirType::DIR_DOWN] = AnimInfo{ 0,0,1,1,false,0.2f };
	_IsaacAnim._headAnim[HeadState::H_IDEL][DirType::DIR_RIGHT] = AnimInfo{ 2,0,1,1,false,0.2f };
	_IsaacAnim._headAnim[HeadState::H_IDEL][DirType::DIR_UP] = AnimInfo{ 4,0,1,1,false, 0.2f };
	_IsaacAnim._headAnim[HeadState::H_IDEL][DirType::DIR_LEFT] = AnimInfo{ 6,0,1,1,false,0.2f };
			  
	_IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_DOWN] = AnimInfo{ 0,0,2,1,false,0.2f };
	_IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_RIGHT] = AnimInfo{ 2,0,2,1,false,0.2f };
	_IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_UP] = AnimInfo{ 4,0,2,1,false,0.2f };
	_IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_LEFT] = AnimInfo{ 6,0,2,1,false,0.2f };

	_IsaacAnim._bodyAnim[BodyState::B_IDEL][DirType::DIR_DOWN] = AnimInfo{ 0,0,1,1,true,0.1f };
	_IsaacAnim._bodyAnim[BodyState::B_IDEL][DirType::DIR_UP] = AnimInfo{ 0,0,1,1,true,0.1f };
	_IsaacAnim._bodyAnim[BodyState::B_IDEL][DirType::DIR_RIGHT] = AnimInfo{ 0,1,1,1,true,0.1f };
	_IsaacAnim._bodyAnim[BodyState::B_IDEL][DirType::DIR_LEFT] = AnimInfo{ 0,1,1,1,true,0.1f,true};
			  
	_IsaacAnim._bodyAnim[BodyState::B_WALK][DirType::DIR_DOWN] = AnimInfo{ 0,0,10,1,true,0.1f };
	_IsaacAnim._bodyAnim[BodyState::B_WALK][DirType::DIR_UP] = AnimInfo{ 0,0,10,1,true,0.1f };
	_IsaacAnim._bodyAnim[BodyState::B_WALK][DirType::DIR_RIGHT] = AnimInfo{ 0,1,10,1,true,0.1f };
	_IsaacAnim._bodyAnim[BodyState::B_WALK][DirType::DIR_LEFT] = AnimInfo{ 0,1,10,1,true,0.1f,true};

	_Head = CreateSpriteComponent("IsaacHead");
	_Body = CreateSpriteComponent("IsaacBody");

	AnimInfo base = _IsaacAnim._bodyAnim[BodyState::B_IDEL][DirType::DIR_DOWN];
	_bodyAnimCtrl.SetAnim(base);
	base = _IsaacAnim._headAnim[HeadState::H_IDEL][DirType::DIR_DOWN];
	_headAnimCtrl.SetAnim(base);

	_sprites.push_back(_Head);
	_sprites.push_back(_Body);

	CreateRectCollider(_Head->GetSize().Width, _Head->GetSize().Height);
}

void Player::Destroy()
{
	Super::Destroy();
	SAFE_DELETE(_Body);
	SAFE_DELETE(_Head);
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
	_playerTearStat.shot_speed = 200.f;

	_currbodyDir = DirType::DIR_DOWN;
	_prevbodyDir = DirType::DIR_DOWN;

	_currbodyState = BodyState::B_IDEL;
	_prevbodyState = BodyState::B_IDEL;

}

void Player::Update(float deltatime)
{
	Super::Update(deltatime);

	_headDir = _currbodyDir;

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
} else {
		_currbodyState = B_IDEL;
}

	// Attack/Head
	if (InputManager::GetInstance()->GetButtonDown(KeyType::Left))
	{
		AnimInfo headInfo = _IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_LEFT];
		_headAnimCtrl.SetAnim(headInfo);
		PlayScene::GetGameScene()->CreateTear(DIR_LEFT, _pos, _playerTearStat,_velocity);
	}
	else if (InputManager::GetInstance()->GetButtonDown(KeyType::Right))
	{
		AnimInfo headInfo = _IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_RIGHT];
		_headAnimCtrl.SetAnim(headInfo);
		PlayScene::GetGameScene()->CreateTear(DIR_RIGHT, _pos, _playerTearStat, _velocity);
	}
	else if (InputManager::GetInstance()->GetButtonDown(KeyType::Up))
	{
		AnimInfo headInfo = _IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_UP];
		_headAnimCtrl.SetAnim(headInfo);
		PlayScene::GetGameScene()->CreateTear(DIR_UP, _pos, _playerTearStat, _velocity);
	}
	else if (InputManager::GetInstance()->GetButtonDown(KeyType::Down))
	{
		AnimInfo headInfo = _IsaacAnim._headAnim[HeadState::H_ATTACK][DirType::DIR_DOWN];
		_headAnimCtrl.SetAnim(headInfo);
		PlayScene::GetGameScene()->CreateTear(DIR_DOWN, _pos, _playerTearStat, _velocity);
	}

	if (_headAnimCtrl.IsEndAnim())
	{
		AnimInfo headInfo = _IsaacAnim._headAnim[HeadState::H_IDEL][DirType::DIR_DOWN];
		_headAnimCtrl.SetAnim(headInfo);
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
	_Body->RenderImage(_dxRenderTarget, _pos + Vector{ 0,5 });
	_Head->RenderImage(_dxRenderTarget,_pos + Vector{0,-10});
	Super::Render(_dxRenderTarget);
}
