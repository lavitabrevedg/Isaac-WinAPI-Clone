#pragma once
#include "Creature.h"

class Player : public Creature
{
	using Super = Creature;
public:
	virtual void Destroy()override;
	virtual void Init()override;

	virtual void Update(float deltatime)override;
	virtual void Render(HDC hdc)override;
private:
	float 
};

