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

public:
	void ChangeGameScene();
	void ChangeEditorScene();

private:
	HWND	_hwnd;	// ������ �ڵ�
	HDC		_hdc;	// �⺻ ��ȭ�� ���� (����Ʈ ����)

	// Double Buffering
	RECT	_rect;              // ������ ����
	HDC		_hdcBack = {};	// ������ ��ȭ�� �غ�
	HBITMAP _bmpBack = {};	// Bitmap ���ٰ� ����Ѵ�.

	class Scene* _currScene = nullptr;	// ���� Ȱ��ȭ�� ���� ������Ʈ/�׷��ش�.
	class Scene* _nextScene = nullptr;	// ���� ���� ��� ������ ���� ƽ�� ����
};

