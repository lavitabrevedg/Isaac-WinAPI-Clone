#pragma once
#include "Scene.h"
//맵툴을 만들면 이제 그 데이터가 룸에 들어가겠지 stage는 그런 룸의 집합?
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

