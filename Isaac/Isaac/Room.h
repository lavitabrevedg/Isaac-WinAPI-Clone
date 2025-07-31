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
	virtual void Render(ID2D1RenderTarget* _dxRenderTarget)override;

	void CreateTear(Vector pos, DirType dir);
private:
	//objectData, mapData
};

