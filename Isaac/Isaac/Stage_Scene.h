#pragma once
#include "Scene.h"

class Stage_Scene//stage는 Room의 집합체 같은 느낌이라 Scene을 상속받는건 좀 아닌듯
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

