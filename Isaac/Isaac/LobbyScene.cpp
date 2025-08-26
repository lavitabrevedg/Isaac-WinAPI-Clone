#include "pch.h"
#include "LobbyScene.h"
#include "Game.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "ImageActor.h"
#include "UIManager.h"
#include "UIBase.h"
#include "UIImage.h"
#include "UITitle.h"

LobbyScene::LobbyScene()
{
}

LobbyScene::~LobbyScene()
{
}

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
	if (InputManager::GetInstance()->GetButtonDown(KeyType::SpaceBar))
	{
		Game::GetInstance()->ChangePlayScene();
	}
}

void LobbyScene::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
}

void LobbyScene::loadResources()
{
	ResourceManager::GetInstance()->LoadDXBitmap("titlemenu", L"Menu/titlemenu.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("titlemenu2", L"Menu/titlemenu2.png", 2, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("titlemenu3", L"Menu/titlemenu3.png", 1, 1);
	
}

void LobbyScene::createObjects()
{
	ImageActor* titlemenu = new ImageActor("titlemenu", GWinSizeX, GWinSizeY);
	titlemenu->Init(Vector{ GWinSizeX / 2, GWinSizeY / 2 });

	ReserveAdd(titlemenu);

}

void LobbyScene::createUI()
{
	UITitle* title = new UITitle();
	_ui->AddPanel(title);
}

void LobbyScene::initTimer()
{
}
