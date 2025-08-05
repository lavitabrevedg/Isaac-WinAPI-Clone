#pragma once
#include "Scene.h"

struct EditorActorInfo
{
	class Actor* tempActor = nullptr;
	int32 spriteIndex = 0;
};

class EditorScene : public Scene
{
	using Super = Scene;
	
public:
	EditorScene();
	~EditorScene();
	
	void Init() override;
	void Destroy() override;
	void Update(float deltatime) override;
	void Render(ID2D1RenderTarget* _dxRenderTarget) override;

	void Save();
	void Load();

	void loadResources() override;
	void createObjects() override;
	void createUI() override;
	void initTimer() override;

protected:
	enum class SELECT_MODE
	{
		ROOM,
		Object,
		Creature,
		COUNT,
	};

	SELECT_MODE _currMode = SELECT_MODE::ROOM;
	EditorActorInfo _editActorInfo[(int32)SELECT_MODE::COUNT];
};

