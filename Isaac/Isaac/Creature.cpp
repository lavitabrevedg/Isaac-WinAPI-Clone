#include "pch.h"
#include "Creature.h"

Creature::Creature()
{
}

Creature::~Creature()
{
}

void Creature::Init(Vector pos)
{
	Super::Init(pos);
}

void Creature::Destroy()
{
	Super::Destroy();
}

void Creature::Update(float deltatime)
{
	Super::Update(deltatime);
    _velocity += _acceleration * deltatime; //속도 = 가속도 * 크기

    if (_velocity.Length() > _maxSpeed)
        _velocity = _velocity.GetNormalize() * _maxSpeed;

    _velocity *= _friction;
    Vector pos = _pos + _velocity * deltatime;
    SetPos(pos);

    _acceleration = Vector(0, 0);
}

void Creature::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
}

void Creature::TakeDamage(float amount)
{
    _hp--;
    if (_hp <= 0)
    {
        Die();
    }
}

void Creature::Die()
{
    _hp++;
}
