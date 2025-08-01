#pragma once
class Stage
{
public:
	void Init();
	void Destroy();
	void Update(float deltatime);
	void Render(ID2D1RenderTarget* _dxRenderTarget);

private:
	vector<class Room*> _Rooms;
};

