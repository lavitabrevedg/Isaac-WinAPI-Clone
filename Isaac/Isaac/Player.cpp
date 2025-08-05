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

	_Head = CreateSpriteComponent("IssacHead", 39, 30);
	//_Body = CreateSpriteComponent("IsaacBodySide", 39, 30);
	//_SideBody = CreateSpriteComponent("IsaacBody", 39, 30);

	CreateRectCollider(_Head->GetSize().Width, _Head->GetSize().Height);
}

void Player::Destroy()
{
	Super::Destroy();
}

void Player::Init(Vector pos)
{
	_pos = pos;
	_maxSpeed = 250.f;
	_friction = 0.95f;
	_velocity = { 0,0 };
	_acceleration = { 0,0 };

	_playerTearStat.damage = 3.5f;
	_playerTearStat.tears = 2.7f;
	_playerTearStat.range = 50.f;
	_playerTearStat.shot_speed = 200.f;
	Super::Init(pos);
}

void Player::Update(float deltatime)
{
	Super::Update(deltatime);

	float moveForce = 1000.f;

	// Move/Body
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::A))
	{
		_acceleration.x -= moveForce; _bodyDir = DIR_LEFT;
	}
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::D))
	{
		_acceleration.x += moveForce; _bodyDir = DIR_RIGHT;
	}
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::W))
	{
		_acceleration.y -= moveForce; _bodyDir = DIR_UP;
	}
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::S))
	{
		_acceleration.y += moveForce; _bodyDir = DIR_DOWN;
	}

	// Attack/Head
	if (InputManager::GetInstance()->GetButtonDown(KeyType::Left))
	{
		_headDir = DIR_LEFT; PlayScene::GetGameScene()->CreateTear(_headDir, _pos, _playerTearStat,_velocity);
	}
	else if (InputManager::GetInstance()->GetButtonDown(KeyType::Right))
	{
		_headDir = DIR_RIGHT; PlayScene::GetGameScene()->CreateTear(_headDir, _pos, _playerTearStat, _velocity);
	}
	else if (InputManager::GetInstance()->GetButtonDown(KeyType::Up))
	{
		_headDir = DIR_UP; PlayScene::GetGameScene()->CreateTear(_headDir, _pos, _playerTearStat, _velocity);
	}
	else if (InputManager::GetInstance()->GetButtonDown(KeyType::Down))
	{
		_headDir = DIR_DOWN; PlayScene::GetGameScene()->CreateTear(_headDir, _pos, _playerTearStat, _velocity);
	}
}

void Player::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
}
