#pragma once
#include "Scene.h"

struct EditorActorInfo
{
	class Actor* tempActor = nullptr;
};

class EditorScene : public Scene
{
	using Super = Scene;

public:
	void Init() override;
	void Destroy() override;
	void Update(float deltatime) override;
	void Render(ID2D1RenderTarget* _dxRenderTarget) override;

	bool useGrid() const override { return true; }

	void Save();
	void Load();

	void loadResources() override;
	void createObjects() override;
	void createUI() override;
	void initTimer() override;

	void OnMouseWheel(int32 delta);

protected:
	enum class SELECT_MODE
	{
		ROOM,
		OBJECT,
		MONSTER,
		COUNT
	};

	SELECT_MODE _currMode = SELECT_MODE::ROOM;
	vector<class Actor*> _editActorInfo[(int32)SELECT_MODE::COUNT];
	int32 _Actorindex = 0;

	int32 _dir[DirType::DIR_MAX] =
	{
		0,
		90,
		180,
		270
	};
	int32 _rotateIndex = 0;
};

