#include "pch.h"
#include "PlayScene.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Player.h"
#include "Tear.h"
#include "Monster.h"
#include "ChaseMonster.h"
#include "DropItem.h"
#include "Stage.h"
#include "Room.h"
#include "InputManager.h"

PlayScene::PlayScene()
{

}

PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	SetCameraPos(Vector{ 0,0 });
	Super::Init();
}

void PlayScene::Destroy()
{
	Super::Destroy();
	_tearPool.Clear();
}

void PlayScene::Update(float deltatime)
{
	if (currentRoom)
	{
		_camera.pos = currentRoom->GetPos();
	}


	for (Tear* tear : _reserveTear)
	{
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
	ResourceManager::GetInstance()->LoadDXBitmap("IsaacHead", L"Player/IsaacHead.png", 8, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("IsaacBody", L"Player/IsaacBody.png", 10, 2);
	ResourceManager::GetInstance()->LoadDXBitmap("Tear", L"Player/Tear.png", 1, 1);

	ResourceManager::GetInstance()->LoadDXBitmap("Monstrobase", L"Monster/Monstrobase.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Fly2", L"Monster/Fly2.png", 4, 4);

	ResourceManager::GetInstance()->LoadDXBitmap("Penny1", L"Items/Penny1.png", 6, 1);

	ResourceManager::GetInstance()->LoadDXBitmap("Tile", L"Room/Tile.png", 1, 1);
}

void PlayScene::createObjects()
{
	_player = new Player();
	_player->Init(Vector(GWinSizeX / 2, GWinSizeY / 2));
	AddActor(_player);

	ChaseMonster* Fly = new ChaseMonster();
	Fly->Init(Vector(GWinSizeX / 2, GWinSizeY / 2));
	ReserveAdd(Fly);

	/*DropItem* Penny = new DropItem();
	Penny->Init(Vector(GWinSizeX / 2, GWinSizeY / 2));
	ReserveAdd(Penny);*/

	_tearPool.Init(100);

	/*for (int i = 0; i < 1; i++)
	{
		Stage* stage = new Stage();
		stage->Init(5);
		stages.push_back(stage);
	}
	int t = stages.size() - 1;
	currentStage = stages[t];
	currentRoom = currentStage->_rooms[0];*/

	Room* room = new Room();
	room->Init(Vector{ 0,0 });   // ¿ùµå ÁÂÇ¥ 0,0
	AddActor(room);
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
		(a.top < b.bottom);
}
