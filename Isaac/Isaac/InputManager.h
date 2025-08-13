#pragma once

#include "Singleton.h"

enum class KeyState
{
	None,
	Press,		// ������ �ִ� ��
	Down,		// ��� ����
	Up,			// ��� ����

	End
};

// ���θ��� ������Ʈ���� �ʿ��� Ű���� ���� ������ ���ش�.
enum class KeyType
{
	LeftMouse = VK_LBUTTON,
	RightMouse = VK_RBUTTON,

	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,
	SpaceBar = VK_SPACE,

	// ������ ���, 1,2
	KEY_1 = '1',
	KEY_2 = '2',

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	L = 'L',
	Q = 'Q',
	E = 'E',
	T = 'T',

	F1 = VK_F1,
	F2 = VK_F2,
	F3 = VK_F3,

	F7 = VK_F7,

};

// �𸮾��� ���
constexpr int32 KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) + 1;

// window api �Լ��� �����ؼ� �츮���� ���� InputSystem �� ������.
class InputManager : public Singleton<InputManager>
{
	friend Singleton<InputManager>;

private:
	InputManager() {}

public:

	void Init(HWND hwnd);
	void Update();

	// Ű���� �Է� ó�� : Ű���尡 ��� ��������? ��� ��������? ������ ���ΰ�?
	// ������ ���� ��
	bool GetButtonPressed(KeyType key) { return GetState(key) == KeyState::Press; }

	// �� ó�� ������ ��
	bool GetButtonDown(KeyType key) { return GetState(key) == KeyState::Down; }

	// �� ó�� �����ٰ� �� ��
	bool GetButtonUp(KeyType key) { return GetState(key) == KeyState::Up; }

	// ���콺 ��ǥ ������
	POINT GetMousePos() { return _mousePos; }

	void SetEventMouseWheel(std::function<void(int32)> event) { _onMouseWheel = event; }
	void OnEventMouseWheel(int32 delta) { if (_onMouseWheel) _onMouseWheel(delta); }

private:
	KeyState GetState(KeyType key) { return _states[static_cast<uint8>(key)]; }

private:
	HWND _hwnd = 0;	// ������ �ڵ�
	vector<KeyState> _states;
	POINT _mousePos = {};

	std::function<void(int32)> _onMouseWheel;
};

