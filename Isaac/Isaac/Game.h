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
	HWND	_hwnd;	// ������ �ڵ�
	HDC		_hdc;	// �⺻ ��ȭ�� ���� (����Ʈ ����)

	// Double Buffering
	RECT	_rect;              // ������ ����
	HDC		_hdcBack = {};	// ������ ��ȭ�� �غ�
	HBITMAP _bmpBack = {};	// Bitmap ���ٰ� ����Ѵ�.

	ID2D1Factory* _dxFactory = nullptr;
	ID2D1HwndRenderTarget* _dxRenderTarget = nullptr;
	IWICImagingFactory* _wicFactory = nullptr;

	class Scene* _currScene = nullptr;	// ���� Ȱ��ȭ�� ���� ������Ʈ/�׷��ش�.
	class Scene* _nextScene = nullptr;	// ���� ���� ��� ������ ���� ƽ�� ����

};
