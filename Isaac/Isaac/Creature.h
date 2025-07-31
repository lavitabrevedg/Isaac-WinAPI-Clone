#pragma once
#include "Actor.h"

enum class State
{
	S_IDLE,
	S_WALK,
	S_ATTACK,
	S_GETUSEITEM,
	S_ONDAMAGE,
	S_MAX
};

class Creature : public Actor
{
	using Super = Actor;
public:
	Creature(Vector pos);
	virtual ~Creature();

protected:
	int _hp;
	float _speed;
	float _atk;
};
