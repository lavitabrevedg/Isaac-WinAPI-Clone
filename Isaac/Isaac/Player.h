#pragma once
#include "Creature.h"

class Player : public Creature
{
	using Super = Creature;
public:
	Player(Vector pos);
	virtual void Destroy()override;
	virtual void Init()override;

	virtual void Update(float deltatime)override;
	virtual void Render(HDC hdc)override;
private:

	DirType HeadDir = DirType::DIR_MAX;
	DirType BodyDir = DirType::DIR_MAX;
	State currentState = State::S_IDLE;
};

