#pragma once
#include "Actor.h"

class Tear : public Actor
{
	using Super = Actor;
public:
	virtual void Destroy()override;
	virtual void Init()override;

	virtual void Update(float deltatime)override;
	virtual void Render(HDC hdc)override;
private:
};

