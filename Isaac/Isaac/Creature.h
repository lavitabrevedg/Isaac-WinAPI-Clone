#pragma once
#include "Actor.h"

class Creature : public Actor
{
	using Super = Actor;
public:
	virtual ~Creature();
	virtual void Destroy()override;
	virtual void Init()override;

	virtual void Update(float deltatime)override;
	virtual void Render(HDC hdc)override;
private:
	int _hp;
	float _speed;
	float _atk;
};

