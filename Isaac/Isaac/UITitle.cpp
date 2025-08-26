#include "pch.h"
#include "UITitle.h"
#include "UIWidget.h"
#include "UIImage.h"
#include "Player.h"
#include "PlayScene.h"
#include "Sprite.h"
#include "Actor.h"

UITitle::UITitle()
{
	_isOpen = true;
	
	_titles = CreateSprite(Vector{ Vector{ GWinSizeX / 2, 360 } }, "titlemenu2", 300, 300);
	UISprite* sp2 = CreateSprite(Vector{ GWinSizeX / 2, 130 }, "titlemenu3", 500, 300);

	AnimInfo tr = { 0,0,2,1,true,0.3f,false };
	_anim = new AnimationController();

	_anim->SetAnim(tr);
}

UITitle::~UITitle()
{
	SAFE_DELETE(_anim);
}

void UITitle::Init()
{

}

void UITitle::Update(float deltaTime)
{
	if (_isOpen == false)
		return;

	Sprite* sp = _titles->GetSprite();
	_anim->Update(deltaTime, sp);
	Super::Update(deltaTime);
}

void UITitle::Render(ID2D1RenderTarget* renderTarget)
{
	if (_isOpen == false)
		return;

	Super::Render(renderTarget);
}
