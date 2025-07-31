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
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update(float deltatime) override;
	virtual void Render(HDC hdc) override;

	void Save();
	void Load();

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

