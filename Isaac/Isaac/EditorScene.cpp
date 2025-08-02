#include "pch.h"
#include "EditorScene.h"
#include "ResourceManager.h"
#include "Player.h"
#include "Monster.h"
#include "Map.h"

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
	ResourceManager::GetInstance()->LoadDXBitmap()
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
