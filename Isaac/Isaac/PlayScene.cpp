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
#include "Sprite.h"
#include "MapData.h"
#include "StageLoader.h"
#include "Effect.h"

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
	if (InputManager::GetInstance()->GetButtonDown(KeyType::F7))
	{
		_gridOn = !_gridOn;
	}

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
	Collide_Player(deltatime);
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

	ResourceManager::GetInstance()->LoadDXBitmap("Guid", L"Room/Guid.png");
	ResourceManager::GetInstance()->LoadDXBitmap("Tile", L"Room/Tile.png");
	ResourceManager::GetInstance()->LoadDXBitmap("Well", L"Room/Well.png");
	ResourceManager::GetInstance()->LoadDXBitmap("Well2", L"Room/Well2.png");
	ResourceManager::GetInstance()->LoadDXBitmap("Well3", L"Room/Well3.png");
	ResourceManager::GetInstance()->LoadDXBitmap("Well4", L"Room/Well4.png");
	ResourceManager::GetInstance()->LoadDXBitmap("Well5", L"Room/Well5.png");
	ResourceManager::GetInstance()->LoadDXBitmap("Well6", L"Room/Well6.png");
	ResourceManager::GetInstance()->LoadDXBitmap("Well7", L"Room/Well7.png");
	ResourceManager::GetInstance()->LoadDXBitmap("Well8", L"Room/Well8.png");
	ResourceManager::GetInstance()->LoadDXBitmap("Well9", L"Room/Well9.png");

	ResourceManager::GetInstance()->LoadDXBitmap("rock", L"Object/rock.png");
	ResourceManager::GetInstance()->LoadDXBitmap("rocks", L"Object/rocks.png");

	ResourceManager::GetInstance()->LoadDXBitmap("TearPop", L"Effect/TearPop.png", 4, 3);
}

void PlayScene::createObjects()
{
	CreateStage(1);
	_player = new Player();
	_player->Init(Vector(200, GWinSizeY / 2));
	ReserveAdd(_player);

	_tearPool.Init(100);

	_gridOn = false;
}

void PlayScene::createUI()
{
}

void PlayScene::initTimer()
{
}

bool PlayScene::CanMove(const Cell* cell)
{
	auto find = _grid.find(*cell);
	if (find != _grid.end())
	{
		return find->second.canMoveCell;
	}
	return false;
}

void PlayScene::CreateTear(DirType dir, Vector pos, TearStat stat, Vector playervelocity)
{
	Tear* playertear = _tearPool.Pull();
	playertear->Init(pos, dir, stat, playervelocity);
	_reserveAdd.insert(playertear);
}

void PlayScene::RemoveTear(Tear* tear)
{
	Sprite* sprite = tear->GetSprite();
	SpawnEffect(tear->GetPos(), "TearPop", sprite->GetSize().Width, sprite->GetSize().Height, EffectAnim::tearEffect);
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

	Vector aCenter{ (a.left + a.right) * 0.5f, (a.top + a.bottom) * 0.5f }; //monster가 tear한테 맞은 방향 + AABB 이걸로 넉백효과 적용
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

void PlayScene::Collide_Player(float dt)
{
	if (_player == nullptr)
		return;
	const RECT* playerRC = _player->GetCollisionRect();
	if (playerRC == nullptr)
		return;

	Cell cell = Cell::ConvertToCell(_player->GetPos(), GridSize);

	for (int dx = -1; dx <= 1; dx++)
	{
		for (int dy = -1; dy <= 1; dy++)
		{
			Cell checkCell{ cell.index_X + dx , cell.index_Y + dy };

			if (checkCell.index_X < 0 || checkCell.index_X >= _gridCountX ||
				checkCell.index_Y < 0 || checkCell.index_Y >= _gridCountY)
				continue;

			const CellInfo& info = GetCellinfo(checkCell);

			for (const auto& otherActor : info._actorsInCell) 
			{
				if (otherActor == _player)
					continue;

				const RECT* targetRC = otherActor->GetCollisionRect();
				if (targetRC == nullptr)
					continue;

				if (AABBIntersect(*playerRC, *targetRC))
				{
					if (otherActor->GetActorType() == ActorType::AT_Monster)
					{
						_player->TakeDamage(1);
					}
					else if (otherActor->GetActorType() == ActorType::AT_Block)
					{
						float playerwid = playerRC->right - playerRC->left;
						float playerhei = playerRC->bottom - playerRC->top;
						float targetwid = targetRC->right - targetRC->left;
						float targethei = targetRC->bottom - targetRC->top;

						Vector playerpos = _player->GetPos();
						Vector targetpos = otherActor->GetPos();

						float xOverlap = min(_player->GetPos().x + playerwid, otherActor->GetPos().x + targetwid) - max(_player->GetPos().x, otherActor->GetPos().x);
						float yOverlap = min(_player->GetPos().y + playerhei, otherActor->GetPos().y + targethei) - max(_player->GetPos().y, otherActor->GetPos().y);

						if (xOverlap < yOverlap)
						{
							if (playerpos.x < targetpos.x)
							{
								Vector pos = Vector(playerpos.x - xOverlap,playerpos.y);
								_player->SetPos(pos);
							}
							else
							{
								Vector pos = Vector(playerpos.x + xOverlap, playerpos.y);
								_player->SetPos(pos);
							}
						}
						else
						{
							if (playerpos.y < targetpos.y)
							{
								Vector pos = Vector(playerpos.x, playerpos.y - yOverlap);
								_player->SetPos(pos);
							}
							else
							{
								Vector pos = Vector(playerpos.x, playerpos.y + yOverlap);
								_player->SetPos(pos);
							}
						}
					}
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

				if (checkCell.index_X < 0 || checkCell.index_X >= _gridCountX ||
					checkCell.index_Y < 0 || checkCell.index_Y >= _gridCountY)
					continue;

				const CellInfo& info = GetCellinfo(checkCell);

				for (const auto& otherActor : info._actorsInCell)
				{
					if (otherActor == _player)
						continue;
					
					const RECT* TargetRC = otherActor->GetCollisionRect();
					if (TargetRC == nullptr)
						continue;

					if (AABBIntersect(*TearRC, *TargetRC))
					{
						if (otherActor->GetActorType() == ActorType::AT_Monster)
						{
							Tear* casttear = dynamic_cast<Tear*>(tear);
							//Monster* monster = dynamic_cast<Monster*>(otherActor);
							float damage = casttear->GetTearstat().damage;
							otherActor->TakeDamage(damage);
							OutputDebugString(L"takeDamage Enemy");

							RemoveTear(casttear);
						}
						else if (otherActor->GetActorType() == ActorType::AT_Block)
						{
							Tear* casttear = dynamic_cast<Tear*>(tear);

							RemoveTear(casttear);
						}
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
	if (file.is_open())
	{
		StageLoader loader;
		_maxMonsterCount = loader.Load(this, file);
		_curMonsterCount = 0;

		file.close();
	}
}

Vector PlayScene::GetPlayerPos()
{
	return _player->GetPos();
}

bool PlayScene::FindPath(Cell start, Cell end, vector<Cell>& findPath, int32 maxDepth)
{
	findPath.clear();

	Heuristic(start, end);
	struct AStarNode
	{
		int g;
		int h;
		Cell data;

		bool operator>(const AStarNode& other) const
		{
			int f = g + h;
			int otherF = other.g + other.h;

			if (f == otherF)
				return g > other.g;

			return f > otherF;
		}
	};
	Cell delta[] =
	{
		Cell(-1, 0), // Left
		Cell(1, 0), // Right
		Cell(0, -1), // Up
		Cell(0, 1), // Down
		Cell(-1, 1), // Left-Down
		Cell(1, 1), // Right-Down
		Cell(-1, -1), // Left-Up
		Cell(1, -1), // Right-Up
	};

	int cost[] =
	{
		10,
		10,
		10,
		10,
		14,
		14,
		14,
		14
	};
	int gridx = _gridCountX + 1;
	int gridy = _gridCountY + 1;

	vector<vector<int>> best(gridy, vector<int>(gridx, INT32_MAX));
	vector<vector<bool>> closed(gridy, vector<bool>(gridx, false));
	vector<vector<Cell>> parent(gridy, vector<Cell>(gridx, Cell(-1, -1)));
	priority_queue<AStarNode, vector<AStarNode>, greater<AStarNode>> pq;

	{
		int g = 0;
		int h = Heuristic(start, end);
		int f = g + h;
		pq.push(AStarNode{g, h, start});
		best[start.index_Y][start.index_X] = f;
		parent[start.index_Y][start.index_X] = start;
	}

	int count = 0;
	while (pq.empty() == false)
	{
		AStarNode node = pq.top();
		pq.pop();

		++count;

		if (closed[node.data.index_Y][node.data.index_X])
			continue;

		if (best[node.data.index_Y][node.data.index_X] < node.g + node.h)
		{
			continue;
		}

		closed[node.data.index_Y][node.data.index_X] = true;

		if (node.data == end)
			break;

		for (int i = 0; i < 8; i++)
		{
			Cell nextCell;
			nextCell.index_X = node.data.index_X + delta[i].index_X;
			nextCell.index_Y = node.data.index_Y + delta[i].index_Y;

			if (CanMove(&nextCell) == false)
				continue;

			if (closed[nextCell.index_Y][nextCell.index_X])
				continue;

			int g = node.g + cost[i];
			int h = Heuristic(nextCell, end);
			int f = g + h;

			if (best[nextCell.index_Y][nextCell.index_X] <= f)
				continue;

			best[nextCell.index_Y][nextCell.index_X] = f;
			pq.push(AStarNode{ g,h,nextCell });
			parent[nextCell.index_Y][nextCell.index_X] = node.data;
		}
	}

	while (true)
	{
		if (end == Cell(-1, -1))
			break;

		findPath.push_back(end);

		if (end == parent[end.index_Y][end.index_X])
		{
			break;
		}

		end = parent[end.index_Y][end.index_X];
	}

	reverse(findPath.begin(), findPath.end());
	return false;
}

void PlayScene::SpawnEffect(Vector pos, string sprite, int32 width, int32 heigh, AnimInfo info)
{
	Effect* effect = new Effect(sprite, width, heigh);
	effect->Init(pos, info);
	ReserveAdd(effect);
}
