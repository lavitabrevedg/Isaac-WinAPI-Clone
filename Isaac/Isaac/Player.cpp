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

	_Head = CreateSpriteComponent("IssacHead", 39, 30);
	//_Body = CreateSpriteComponent("IsaacBodySide", 39, 30);
	//_SideBody = CreateSpriteComponent("IsaacBody", 39, 30);
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

	float mess = 1.1f;
	float moveForce = 500;
	Vector acceleration = { 0,0 };

	if (InputManager::GetInstance()->GetButtonPressed(KeyType::A)) { acceleration.x -= moveForce / mess; BodyDir = DIR_LEFT; }
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::D)) { acceleration.x += moveForce / mess; BodyDir = DIR_RIGHT;}
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::W)) { acceleration.y -= moveForce / mess; BodyDir = DIR_UP; }
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::S)) { acceleration.y += moveForce / mess; BodyDir = DIR_DOWN; }

	if (InputManager::GetInstance()->GetButtonPressed(KeyType::Left)) { HeadDir = DIR_LEFT; }
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::Right)) { HeadDir = DIR_RIGHT; }
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::Up)) { HeadDir = DIR_UP; }
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::Down)) { HeadDir = DIR_DOWN; }

	_pos += acceleration * deltatime;
}

void Player::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
}
