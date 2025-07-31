#pragma once
#include "Singleton.h"

class Game : public Singleton<Game>
{
	friend Singleton<Game>;

protected:
	Game() {};
public:
	void Init(HWND hwnd);
	void Destroy();

	void Update();
	void Render();

	HWND GetHwnd() { return _hwnd; }
	class Scene* GetCurrScene() { return _currScene; }

	ID2D1HwndRenderTarget* GetRenderTarget() { return _dxRenderTarget; }
	IWICImagingFactory* GetWICFactory() { return _wicFactory; }

	Vector ConvertScreenPos(Vector worldPos);
	Vector ConvertWorldPos(Vector screenPos);

public:
	void ChangeLobbyScene();
	void ChangeRoomScene();
	void ChangeEditorScene();

	void LoadTexture(wstring path, int maxCountX, int maxCountY);

private:
	HWND	_hwnd;	// 윈도우 핸들
	HDC		_hdc;	// 기본 도화지 정보 (프론트 버퍼)

	// Double Buffering
	RECT	_rect;              // 버퍼의 영역
	HDC		_hdcBack = {};	// 여분의 도화지 준비
	HBITMAP _bmpBack = {};	// Bitmap 에다가 써야한다.

	ID2D1Factory* _dxFactory = nullptr;
	ID2D1HwndRenderTarget* _dxRenderTarget = nullptr;
	IWICImagingFactory* _wicFactory = nullptr;

	class Scene* _currScene = nullptr;	// 현재 활성화된 씬만 업데이트/그려준다.
	class Scene* _nextScene = nullptr;	// 현재 씬이 모두 끝나고 다음 틱에 변경

};
