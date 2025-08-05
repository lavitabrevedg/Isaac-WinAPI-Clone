#include "pch.h"
#include "Scene.h"
#include "Actor.h"



Scene::Scene()
{
}

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

	for (auto iter : _reserveRemove)
	{
		RemoveActor(iter);
	}
	_reserveRemove.clear();

	for (auto iter : _reserveAdd)
	{
		AddActor(iter);
	}
	_reserveAdd.clear();
}

void Scene::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	for (auto list : _renderList)
	{
		for (auto iter : list)
		{
			iter->Render(_dxRenderTarget);
		}
	}
}

void Scene::RemoveActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	if (actor->GetRenderLayer() < 0 || actor->GetRenderLayer() >= RenderLayer::RL_Count)
		return;

	{
		auto& list = _renderList[actor->GetRenderLayer()];
		auto iter = std::find(list.begin(), list.end(), actor);
		if (iter != list.end())
		{
			list.erase(iter);
		}
	}

	{
		auto iter = _actors.find(actor);
		if (iter != _actors.end())
		{
			_actors.erase(iter);
			delete actor;
		}
	}
}

void Scene::AddActor(Actor* actor)
{
	if (actor == nullptr)
		return;
	if (actor->GetRenderLayer() < 0 || actor->GetRenderLayer() >= RenderLayer::RL_Count)
		return;

	_actors.insert(actor);
	_renderList[actor->GetRenderLayer()].push_back(actor);
}

void Scene::ReserveRemove(Actor* actor)
{
	if (nullptr == actor)
		return;

	if (_reserveRemove.contains(actor))
		return;

	_reserveRemove.emplace(actor);
}

void Scene::ReserveAdd(Actor* actor)
{
	if (nullptr == actor)
		return;

	if (_reserveAdd.contains(actor))
		return;

	_reserveAdd.emplace(actor);
}