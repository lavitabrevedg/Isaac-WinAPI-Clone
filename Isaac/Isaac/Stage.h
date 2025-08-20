#pragma once
class Stage
{
public:
	Stage();
	void Init(int32 roomsize);
	void Destroy();
	void Update(float deltatime);
	void Render(ID2D1RenderTarget* _dxRenderTarget);

public:
};

