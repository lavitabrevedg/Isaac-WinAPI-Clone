#include "pch.h"
#include "LobbyScene.h"
#include "Game.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Map.h"

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
	Map* Mainmap = new Map();
	Mainmap->Init(Vector{ 0,0 });
	_actors.insert(Mainmap);
}

void LobbyScene::createUI()
{
}

void LobbyScene::initTimer()
{
}
