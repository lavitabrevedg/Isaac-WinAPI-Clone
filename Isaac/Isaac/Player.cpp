#include "pch.h"
#include "Player.h"
#include "Game.h"
#include "Scene.h"
#include "InputManager.h"
#include "Tear.h"
#include "Room.h"

Player::Player(Vector pos) : Super(pos)
{
	_pos = pos;
	_hp = 3;
	_atk = 3.5f;
	_speed = 500.f;
}

void Player::Destroy()
{
	Super::Destroy();
}

void Player::Init()
{
	Super::Init();

}

void Player::Update(float deltatime)
{
	Super::Update(deltatime);

	if (InputManager::GetInstance()->GetButtonPressed(KeyType::A)) { _pos.x -= _speed * deltatime; BodyDir = DIR_LEFT; }
	else if (InputManager::GetInstance()->GetButtonPressed(KeyType::D)) { _pos.x += _speed * deltatime; BodyDir = DIR_RIGHT;}
	else if (InputManager::GetInstance()->GetButtonPressed(KeyType::W)) { _pos.y -= _speed * deltatime; BodyDir = DIR_UP; }
	else if (InputManager::GetInstance()->GetButtonPressed(KeyType::S)) { _pos.y += _speed * deltatime; BodyDir = DIR_DOWN; }

	if (InputManager::GetInstance()->GetButtonPressed(KeyType::Left)) { HeadDir = DIR_LEFT; }
	else if (InputManager::GetInstance()->GetButtonPressed(KeyType::Right)) { HeadDir = DIR_RIGHT; }
	else if (InputManager::GetInstance()->GetButtonPressed(KeyType::Up)) { HeadDir = DIR_UP; }
	else if (InputManager::GetInstance()->GetButtonPressed(KeyType::Down)) { HeadDir = DIR_DOWN; }
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}
