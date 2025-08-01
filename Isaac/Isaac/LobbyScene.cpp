#include "pch.h"
#include "LobbyScene.h"
#include "Game.h"
#include "InputManager.h"
#include "ResourceManager.h"

void LobbyScene::Init()
{
	Super::Init();
}

void LobbyScene::Destroy()
{
	Super::Destroy();
}

void LobbyScene::Update(float deltatime)
{
	Super::Update(deltatime);
	if (InputManager::GetInstance()->GetButtonDown(KeyType::F1))
	{
		Game::GetInstance()->ChangeEditorScene();
	}
}

void LobbyScene::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
}

void LobbyScene::loadResources()
{
	ResourceManager::GetInstance()->LoadDXBitmap("titlemenu", L"Menu/titlemenu.png", 1, 2);
	
}

void LobbyScene::createObjects()
{
}

void LobbyScene::createUI()
{
}

void LobbyScene::initTimer()
{
}
