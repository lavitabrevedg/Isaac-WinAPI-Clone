#include "pch.h"
#include "PlayScene.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Player.h"
#include "Tear.h"
#include "Monster.h"
#include "DropItem.h"
#include "Stage.h"
#include "Room.h"
#include "InputManager.h"
#include "MapData.h"
#include "StageLoader.h"

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
	//if (currentRoom)
	//{
	//	_camera.pos = currentRoom->GetPos();
	//}

	Super::Update(deltatime);

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

	Collide_PlayerTears(deltatime);
	Collide_PlayerVsMonsters(deltatime);
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
	ResourceManager::GetInstance()->LoadDXBitmap("gaperHead", L"Monster/gaperHead.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("gaperBody", L"Monster/gaperBody.png", 10, 2);

	ResourceManager::GetInstance()->LoadDXBitmap("Penny1", L"Items/Penny1.png", 6, 1);

	ResourceManager::GetInstance()->LoadDXBitmap("Guid", L"Room/Guid.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Tile", L"Room/Tile.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well", L"Room/Well.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well2", L"Room/Well2.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well3", L"Room/Well3.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well4", L"Room/Well4.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well5", L"Room/Well5.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well6", L"Room/Well6.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well7", L"Room/Well7.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well8", L"Room/Well8.png", 1, 1);
	ResourceManager::GetInstance()->LoadDXBitmap("Well9", L"Room/Well9.png", 1, 1);
}

void PlayScene::createObjects()
{
	CreateStage(1);
	_player = new Player();
	_player->Init(Vector(GWinSizeX / 2, GWinSizeY / 2));
	ReserveAdd(_player);

	_tearPool.Init(100);
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

bool PlayScene::ComputeMTVAndDir(const RECT& a, const RECT& b, Vector& outMTV, Vector& outDir)
{
	if (!AABBIntersect(a, b)) return false;

	Vector aCenter{ (a.left + a.right) * 0.5f, (a.top + a.bottom) * 0.5f };
	Vector bCenter{ (b.left + b.right) * 0.5f, (b.top + b.bottom) * 0.5f };
	outDir = (aCenter - bCenter);
	float len2 = outDir.LengthSquared();
	if (len2 > 0.0001f)
	{
		float invLen = 1.0f / sqrtf(len2);
		outDir.x *= invLen; outDir.y *= invLen;
	}
	else
	{
		outDir = Vector{ 0,-1 };
	}

	float dx1 = (float)b.right - (float)a.left;
	float dx2 = (float)a.right - (float)b.left;
	float mx = (dx1 < dx2) ? dx1 : -dx2;

	float dy1 = (float)b.bottom - (float)a.top;
	float dy2 = (float)a.bottom - (float)b.top;
	float my = (dy1 < dy2) ? dy1 : -dy2;

	outMTV = (fabsf(mx) < fabsf(my)) ? Vector{ mx,0 } : Vector{ 0,my };
	return true;
}

void PlayScene::Collide_PlayerVsMonsters(float dt)
{
	if (_player == nullptr)
		return;
	const RECT* PlayerRC = _player->GetCollisionRect();
	if (PlayerRC == nullptr)
		return;

	Cell cell = Cell::ConvertToCell(_player->GetPos(), GridSize);

	for (int dx = -1; dx <= 1; dx++)
	{
		for (int dy = -1; dy <= 1; dy++)
		{
			Cell checkCell{ cell.index_X + dx , cell.index_Y + dy };

			if (checkCell.index_X < 0 || checkCell.index_Y < 0)
				continue;

			CellInfo info = GetCellinfo(checkCell);

			for (const auto& otherActor : info._actorsInCell) //@TODO 오류 왜뜨는거야 ㅅㅂㅅㅂㅅㅂ
			{
				if (otherActor == _player)
					continue;

				if (otherActor->GetActorType() != ActorType::AT_Monster)
					continue;

				const RECT* MonsterRC = otherActor->GetCollisionRect();
				if (MonsterRC == nullptr)
					continue;

				if (AABBIntersect(*PlayerRC, *MonsterRC))
				{
					_player->OnDamage(1);
					
					OutputDebugString(L"takeDamage Player");
					/*if (otherActor->GetRenderLayer() == RenderLayer::RL_Tear)
					{
						RemoveTear(otherActor);
					}*/
				}
			}
		}
	}
}

void PlayScene::Collide_PlayerTears(float dt)
{
	auto& tearList = _renderList[RenderLayer::RL_Tear];

	for (auto& tear : tearList)
	{
		const RECT* TearRC = tear->GetCollisionRect();
		if (TearRC == nullptr)
			continue;

		Cell cell = Cell::ConvertToCell(tear->GetPos(), GridSize);

		for (int dx = -1; dx <= 1; dx++)
		{
			for (int dy = -1; dy <= 1; dy++)
			{
				Cell checkCell{ cell.index_X + dx , cell.index_Y + dy };

				if (checkCell.index_X < 0 || checkCell.index_Y < 0)
					continue;

				CellInfo info = GetCellinfo(checkCell);

				for (const auto& otherActor : info._actorsInCell)
				{
					if (otherActor == _player)
						continue;

					if (otherActor->GetActorType() != ActorType::AT_Monster)
						continue;

					const RECT* MonsterRC = otherActor->GetCollisionRect();
					if (MonsterRC == nullptr)
						continue;

					if (AABBIntersect(*TearRC, *MonsterRC))
					{
						Monster* monster = dynamic_cast<Monster*>(otherActor);
						Tear* casttear = dynamic_cast<Tear*>(tear);
						int32 damage = casttear->GetTearstat().damage;

						monster->OnDamage(damage);

						OutputDebugString(L"takeDamage Enemy");

						RemoveTear(casttear);
					}
				}
			}
		}
	}
}

void PlayScene::CreateStage(int32 stage)
{
	wstring fileName = std::format(L"Room_{0}.json", stage);
	fs::path fullPath = fs::current_path() / L"../Resources/" / fileName;

	std::wifstream file(fullPath);
	if (file.is_open());
	{
		StageLoader loader;
		_maxMonsterCount = loader.Load(this, file);
		_curMonsterCount = 0;

		file.close();
	}
}
