#include "pch.h"
#include "Scene.h"
#include "Map.h"

Scene::~Scene()
{
}

void Scene::Init()
{
	// 리소스 로드
	loadResources();

	// 오브젝트 생성
	createObjects();

	// UI 생성
	createUI();

	// 타이머 추가
	initTimer();

}

void Scene::Destroy()
{
	for (auto iter : _actors)
	{
		iter->Destroy();
		SAFE_DELETE(iter);
	}
	_actors.clear();
}

void Scene::Update(float deltatime)
{
	for (auto iter : _actors)
	{
		iter->Update(deltatime);
	}
}

void Scene::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	for (auto iter : _actors)
	{
		iter->Render(_dxRenderTarget);
	}
}
