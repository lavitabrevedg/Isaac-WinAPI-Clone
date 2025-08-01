#include "pch.h"
#include "Scene.h"
#include "Map.h"

Scene::~Scene()
{
}

void Scene::Init()
{
	// ���ҽ� �ε�
	loadResources();

	// ������Ʈ ����
	createObjects();

	// UI ����
	createUI();

	// Ÿ�̸� �߰�
	initTimer();

	Map* Mainmap = new Map(Vector{ GWinSizeX / 2,GWinSizeY / 2 });
	_actors.insert(Mainmap);
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
