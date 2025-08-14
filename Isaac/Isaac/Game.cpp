#include "pch.h"
#include "Game.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"

#include "LobbyScene.h"
#include "Stage.h"
#include "EditorScene.h"
#include "Room.h"
#include "PlayScene.h"

void Game::Init(HWND hwnd)
{
	srand((uint32)time(0));
	_hwnd = hwnd;
	//_hdc = ::GetDC(hwnd);

	GetClientRect(hwnd, &_rect);

	/*_hdcBack = CreateCompatibleDC(_hdc);
	_bmpBack = CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);
	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack);
	DeleteObject(prev);*/

	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_dxFactory);

	D2D1_SIZE_U size = D2D1::SizeU(_rect.right - _rect.left, _rect.bottom - _rect.top);

	// Create a Direct2D render target.
	_dxFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd, size),
		&_dxRenderTarget);

	// 이미지 로드 초기화
	CoInitialize(NULL);
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_wicFactory));

	wchar_t buffer[MAX_PATH];
	DWORD length = ::GetCurrentDirectory(MAX_PATH, buffer);
	fs::path currentPath = fs::path(buffer) / L"../Resources/";
	ResourceManager::GetInstance()->Init(hwnd, currentPath);
	
	TimeManager::GetInstance()->Init();
	InputManager::GetInstance()->Init(hwnd);

	_currScene = new LobbyScene();
	_currScene->Init();
}

void Game::Destroy()
{
	InputManager::DestroyInstance();
	TimeManager::DestroyInstance();
	ResourceManager::DestroyInstance();


	if (_currScene)
	{
		_currScene->Destroy();
		SAFE_DELETE(_currScene);
	}

	SAFE_RELEASE(_dxFactory);
	SAFE_RELEASE(_dxRenderTarget);
	SAFE_RELEASE(_wicFactory);
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

	TimeManager::GetInstance()->Update();
	InputManager::GetInstance()->Update();
	ResourceManager::GetInstance()->Update(TimeManager::GetInstance()->GetDeltaTime());

	if (_currScene)
	{
		_currScene->Update(TimeManager::GetInstance()->GetDeltaTime());
	}
}

void Game::Render()
{
	_dxRenderTarget->BeginDraw();
	_dxRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));


	if (_currScene)
	{
		_currScene->Render(_dxRenderTarget);
	}

	uint32 fps = TimeManager::GetInstance()->GetFps();
	float deltatime = TimeManager::GetInstance()->GetDeltaTime();

	auto brush = ResourceManager::GetInstance()->GetBrush(BrushColor::White);
	auto font = ResourceManager::GetInstance()->GetFont(FontSize::FONT_12);

	{
		POINT mousePos = InputManager::GetInstance()->GetMousePos();
		wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		_dxRenderTarget->DrawTextW(
			str.c_str(),
			(uint32)str.size(),
			font,
			D2D1::RectF(300, 10, 600, 200),
			brush
		);
	}

	{
		wstring str = std::format(L"FPS({0}), DT({1})", fps, deltatime);
		_dxRenderTarget->DrawTextW(
			str.c_str(),
			(uint32)str.size(),
			font,
			D2D1::RectF(5, 10, 600, 200),
			brush
		);
	}

	_dxRenderTarget->EndDraw();
}

void Game::ChangeLobbyScene()
{
	if (_nextScene)
	{
		SAFE_DELETE(_nextScene);
	}
	
	_nextScene = new LobbyScene;
}

void Game::ChangePlayScene()
{
	if (_nextScene)
	{
		SAFE_DELETE(_nextScene);
	}

	_nextScene = new PlayScene;
}

void Game::ChangeEditorScene()
{
	if (_nextScene)
	{
		SAFE_DELETE(_nextScene);
	}

	_nextScene = new EditorScene;
}

Vector Game::ConvertScreenPos(Vector worldPos)
{
	if (GetCurrScene())
	{
		Vector cameraPos = GetCurrScene()->GetCameraPos();
		Vector pos;
		pos.x = worldPos.x - (cameraPos.x - GWinSizeX / 2);
		pos.y = worldPos.y - (cameraPos.y - GWinSizeY / 2);
		return pos;
	}
	return worldPos;
}

Vector Game::ConvertWorldPos(Vector screenPos)
{
	if (GetCurrScene())
	{
		Vector cameraPos = GetCurrScene()->GetCameraPos();
		Vector pos;
		pos.x = screenPos.x + (cameraPos.x - GWinSizeX / 2);
		pos.y = screenPos.y + (cameraPos.y - GWinSizeY / 2);
		return pos;
	}
	return screenPos;
}