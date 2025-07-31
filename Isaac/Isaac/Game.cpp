#include "pch.h"
#include "Game.h"
#include "InputManager.h"
#include "TimeManager.h"

#include "LobbyScene.h"
#include "Stage_Scene.h"
#include "EditorScene.h"

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_hdc = ::GetDC(hwnd);

	GetClientRect(hwnd, &_rect);

	_hdcBack = CreateCompatibleDC(_hdc);

	_bmpBack = CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);

	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack);
	DeleteObject(prev);

	InputManager::GetInstance()->Init(hwnd);
	TimeManager::GetInstance()->Init();

	_currScene = new LobbyScene();
	_currScene->Init();

}

void Game::Destroy()
{
	InputManager::DestroyInstance();
	TimeManager::DestroyInstance();

	if (_currScene)
	{
		_currScene->Destroy();
	}
	SAFE_DELETE(_currScene);
}

void Game::Update()
{
	if (_nextScene)
	{
		if (_currScene)
		{
			_currScene->Destroy();
			SAFE_DELETE(_currScene);
		}

		_currScene = _nextScene;
		_currScene->Init();

		_nextScene = nullptr;
	}

	InputManager::GetInstance()->Update();
	TimeManager::GetInstance()->Update();

	if (_currScene)
	{
		_currScene->Update(TimeManager::GetInstance()->GetDeltaTime());
		_currScene->PostUpdate(TimeManager::GetInstance()->GetDeltaTime());
	}
}

void Game::Render()
{
	uint32 fps = TimeManager::GetInstance()->GetFps();
	float deltatime = TimeManager::GetInstance()->GetDeltaTime();

	{
		POINT mousePos = InputManager::GetInstance()->GetMousePos();
		wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(_hdcBack, 300, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	{
		wstring str = std::format(L"FPS({0}), DT({1})", fps, deltatime);
		::TextOut(_hdcBack, 5, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	if (_currScene)
	{
		_currScene->Render(_hdcBack);
	}

	BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY);

	PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}
