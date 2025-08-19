#include "pch.h"
#include "Effect.h"
#include "Game.h"
#include "PlayScene.h"
#include "Sprite.h"

Effect::Effect(string spriteName, int32 width, int32 height)
{
	_sprite = CreateSpriteComponent(spriteName,width,height);
}

void Effect::Init(Vector pos, AnimInfo info)
{
	_pos = pos;
	AnimInfo anim = info;
	_effectAnim.SetAnim(anim);
}

void Effect::Update(float deltatime)
{
	_effectAnim.Update(deltatime,_sprite);

	if (_effectAnim.IsEndAnim())
	{
		Game::GetInstance()->GetCurrScene()->ReserveRemove(this);
	}
}

void Effect::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	_sprite->RenderImage(_dxRenderTarget, _pos);
}

void Effect::Destroy()
{
	Super::Destroy();
}
