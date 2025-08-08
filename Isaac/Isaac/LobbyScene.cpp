#include "pch.h"
#include "LobbyScene.h"
#include "Game.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "ImageActor.h"

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
}

void LobbyScene::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
}

void LobbyScene::loadResources()
{
	ResourceManager::GetInstance()->LoadDXBitmap("titlemenu", L"Menu/titlemenu.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("titlemenu2", L"Menu/titlemenu2.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("titlemenu3", L"Menu/titlemenu3.png", 1, 1);
	
}

void LobbyScene::createObjects()
{
	ImageActor* titlemenu = new ImageActor("titlemenu", 300, 300);
	ImageActor* titlemenu2 = new ImageActor("titlemenu2", 300, 300);
	ImageActor* titlemenu3 = new ImageActor("titlemenu3", 300, 300);

	titlemenu->Init(Vector{ GWinSizeX / 2, GWinSizeY / 2 });
	titlemenu2->Init(Vector{ GWinSizeX / 2, GWinSizeY / 2 });
	titlemenu3->Init(Vector{ GWinSizeX / 2, GWinSizeY / 2 });

	ReserveAdd(titlemenu);
	ReserveAdd(titlemenu2);
	ReserveAdd(titlemenu3);
}

void LobbyScene::createUI()
{
}

void LobbyScene::initTimer()
{
}
