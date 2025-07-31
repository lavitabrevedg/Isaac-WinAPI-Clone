#include "pch.h"
#include "LobbyScene.h"
#include "Game.h"
#include "InputManager.h"

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

void LobbyScene::Render(HDC hdc)
{
	Super::Render(hdc);
}
