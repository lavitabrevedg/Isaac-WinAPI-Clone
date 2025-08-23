#include "pch.h"
#include "UIHud.h"
#include "UIWidget.h"
#include "UIImage.h"
#include "Player.h"
#include "PlayScene.h"


UIHud::UIHud()
{
	_isOpen = true;

	Vector pos = { 20,30 };
	_gameHud = CreateImage(pos, "P_Heart", 30, 30); //@TODO 추가해줘야함
}

void UIHud::Init()
{
}

void UIHud::Update(float deltaTime)
{
	if (_isOpen == false)
		return;

	Super::Update(deltaTime);

	Player* player = PlayScene::GetGameScene()->GetPlayer();

	if (player == nullptr)
		return;
	
	if (_gameHud)
	{
		int32 maxhp = player->GetMaxHp();
		int32 currhp = player->GetCurrHp(); //다 그려놓고 안보이게 숨겨놔야하나..

		for (int i = 0; i < maxhp; i++)
		{

		}
	}
}

void UIHud::Render(ID2D1RenderTarget* renderTarget)
{
	if (_isOpen == false)
		return;


}
