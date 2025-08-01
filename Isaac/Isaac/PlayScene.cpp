#include "pch.h"
#include "PlayScene.h"
#include "ResourceManager.h"
#include "Stage.h"
#include "Room.h"
#include "Player.h"
#include "Game.h"

void PlayScene::Init()
{
	Super::Init();
}

void PlayScene::Destroy()
{
	Super::Destroy();
}

void PlayScene::Update(float deltatime)
{
	Super::Update(deltatime);
}

void PlayScene::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
}

void PlayScene::loadResources()
{
	ResourceManager::GetInstance()->LoadDXBitmap("IssacHead", L"Player/IsaacHead.png", 8, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("IsaacBodyLeftRight", L"Player/IsaacBodyLeftRight.png", 10, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("IsaacBodyUpDown", L"Player/IsaacBodyUpDown.png", 10, 1);
}

void PlayScene::createObjects()
{
}

void PlayScene::createUI()
{
}

void PlayScene::initTimer()
{
}
