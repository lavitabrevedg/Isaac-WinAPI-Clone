#pragma once
#include "Scene.h"
//������ ����� ���� �� �����Ͱ� �뿡 ������ stage�� �׷� ���� ����?
class Room : public Scene
{
	using Super = Scene;
public:
	virtual void Init()override;
	virtual void Destroy()override;
	virtual void Update(float deltatime)override;
	virtual void Render(HDC hdc)override;

	void CreateTear(Vector pos, DirType dir);
private:
	//objectData, mapData
};

