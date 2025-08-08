#include "pch.h"
#include "EditorScene.h"
#include "ResourceManager.h"
#include "Player.h"
#include "Monster.h"

EditorScene::EditorScene()
{
}

EditorScene::~EditorScene()
{
}

void EditorScene::Init()
{
	Super::Init();
}

void EditorScene::Destroy()
{
	Super::Destroy();
}

void EditorScene::Update(float deltatime)
{
	Super::Update(deltatime);
}

void EditorScene::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
}

void EditorScene::Save()
{

}

void EditorScene::Load()
{

}

void EditorScene::loadResources()
{
	ResourceManager::GetInstance()->LoadDXBitmap("Guid", L"Room/Guid.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Tile", L"Room/Tile.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well", L"Room/Well.png", 1, 1);

	ResourceManager::GetInstance()->LoadDXBitmap("Combat", L"Monster/Combat.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Fly", L"Monster/Fly.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Fly2", L"Monster/Fly2.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Monstro", L"Monster/Monstro.png", 1, 1);

	ResourceManager::GetInstance()->LoadDXBitmap("Bomb", L"Items/Bomb.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Chest", L"Items/Chest.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Heart", L"Items/Heart.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Key", L"Items/Key.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Penny1", L"Items/Penny1.png", 1, 1);
}

void EditorScene::createObjects()
{

}

void EditorScene::createUI()
{

}

void EditorScene::initTimer()
{

}
