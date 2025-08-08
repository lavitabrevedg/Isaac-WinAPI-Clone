#pragma once
class Stage
{
public:
	Stage();
	void Init(int32 roomsize);
	void Destroy();
	void Update(float deltatime);
	void Render(ID2D1RenderTarget* _dxRenderTarget);

	int roonNumber = 0;
	//void ChangeNextRoom();

	//Room* GetCurrentRoom() { return _rooms[0]; }

public:
	vector<class Room*> _rooms;
};

