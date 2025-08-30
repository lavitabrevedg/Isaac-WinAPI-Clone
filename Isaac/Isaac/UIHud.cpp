#include "pch.h"
#include "UIHud.h"
#include "UIWidget.h"
#include "UIImage.h"
#include "Player.h"
#include "PlayScene.h"
#include "Sprite.h"
#include "ResourceManager.h"

UIHud::UIHud()
{
	_isOpen = true;

	Player* player = PlayScene::GetGameScene()->GetPlayer();
	if (player == nullptr)
		return;

	int32 maxhp = (int32)player->GetMaxHp();

	for (int i = 2; i <= maxhp; i += 2)
	{
		UISprite* sp = CreateSprite(Vector(60.f + (i * 13), 30.f), "P_Heart", 28, 28);
		_playerHp.push_back(sp);
	}

	CreateSprite(Vector(20.f, 80.f), "Coin", 30, 30);
	CreateSprite(Vector(20.f, 103.f), "Boom", 30, 30);
	CreateSprite(Vector(20.f, 127.f), "Key", 30, 30);
}

void UIHud::Init()
{
}

void UIHud::Update(float deltaTime)
{
	if (_isOpen == false)
		return;

	Super::Update(deltaTime);
}

void UIHud::Render(ID2D1RenderTarget* renderTarget)
{
	if (_isOpen == false)
		return;

	Super::Render(renderTarget);

	Player* player = PlayScene::GetGameScene()->GetPlayer();
	if (player == nullptr)
		return;

	 int32 coin = player->GetCoins(); //@TODO 플레이어 죽는 순간 -57막 몇만개로 바뀜
	 int32 boom = player->GetBooms();
	 int32 key = player->GetKeys();

	 _coin = coin;
	 _boom = boom;
	 _key = key;

	auto brush = ResourceManager::GetInstance()->GetBrush(BrushColor::White);
	auto font = ResourceManager::GetInstance()->GetFont(FontSize::FONT_20);

	wstring str = std::format(L"{0}\n{1}\n{2}", _coin, _boom, _key);
	renderTarget->DrawTextW(
		str.c_str(),
		(uint32)str.size(),
		font,
		D2D1::RectF(45, 73, 600, 200),
		brush
	);
}

void UIHud::PlayerOnDamage(int32 amount)
{
	for (int i = (int)_playerHp.size() - 1; i >= 0 && amount > 0; --i)
	{
			int32 x, y;
			_playerHp[i]->GetIndex(x, y);

			int canFill = min(amount, 2 - x);
			if(canFill > 0)
			{
			_playerHp[i]->SetIndex(x + canFill, y);
			amount -= canFill;
			}
	}
}
