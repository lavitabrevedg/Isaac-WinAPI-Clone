#include "pch.h"
#include "PlayScene.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Player.h"
#include "Tear.h"

PlayScene::PlayScene()
{

}

PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	Super::Init();
	_tearPool.Init(100);
}

void PlayScene::Destroy()
{
	Super::Destroy();
	_tearPool.Clear();
}

void PlayScene::Update(float deltatime)
{
	for (Tear* tear : _reserveTear)
	{
		// 컨테이너에서 안전하게 삭제
		_actors.erase(tear);

		auto& list = _renderList[RenderLayer::RL_Tear];
		auto iter = std::find(list.begin(), list.end(), tear);
		if (iter != list.end())
			list.erase(iter);

		_tearPool.RePush(tear);
	}

	_reserveTear.clear();
	Super::Update(deltatime);
}

void PlayScene::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	Super::Render(_dxRenderTarget);
}

PlayScene* PlayScene::GetGameScene()
{
	return dynamic_cast<PlayScene*>(Game::GetInstance()->GetCurrScene());
}

void PlayScene::loadResources()
{
	ResourceManager::GetInstance()->LoadDXBitmap("IssacHead", L"Player/IsaacHead.png", 8, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("IsaacBodySide", L"Player/IsaacBodySide.png", 10, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("IsaacBody", L"Player/IsaacBody.png", 10, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Tear", L"Player/Tear.png", 1, 1);
}

void PlayScene::createObjects()
{
	Player* player = new Player();
	player->Init(Vector(GWinSizeX / 2, GWinSizeY / 2));
	AddActor(player);
}

void PlayScene::createUI()
{
}

void PlayScene::initTimer()
{
}

void PlayScene::CreateTear(DirType dir, Vector pos, TearStat stat, Vector playervelocity)
{
	Tear* playertear = _tearPool.Pull();
	playertear->Init(pos, dir, stat, playervelocity);
	_reserveAdd.insert(playertear);
}

void PlayScene::RemoveTear(Tear* tear)
{
	_reserveTear.push_back(tear);
}

bool PlayScene::AABBIntersect(const RECT& a, const RECT& b)
{
	return (a.right > b.left) &&
		(a.left < b.right) &&
		(a.bottom > b.top) &&
		(a.top < b.bottom); //@TODO 충돌체크해봐야함
}
