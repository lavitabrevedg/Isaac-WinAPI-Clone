#pragma once
#include "Scene.h"

class Stage_Scene//stage�� Room�� ����ü ���� �����̶� Scene�� ��ӹ޴°� �� �ƴѵ�
{
	using Super = Scene;

public:
	void Init();
	void Destroy();
	void Update(float deltatime);
	void Render(HDC hdc);

private:
	vector<class Room*> _Rooms;
};

