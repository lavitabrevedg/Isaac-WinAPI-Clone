#pragma once

class Room
{
public:
	void Init();
	void Destroy();
	void Update(float deltatime);
	void Render(ID2D1RenderTarget* _dxRenderTarget);

	void CreateTear(Vector pos, DirType dir);

	
private:
	//objectData, mapData
};

