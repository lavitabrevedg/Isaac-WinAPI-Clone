#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "ResourceManager.h"
#include "Game.h"
#include "UIManager.h"

Scene::Scene()
{
	_ui = new UIManager(); //@TODO 삭제 delete해줘야함 
	_ui->Init();
}

Scene::~Scene()
{
}

void Scene::Init()
{
	// 리소스 로드
	loadResources();

	//그리드 생성
	if (useGrid()) CreateGrid();

	// 오브젝트 생성
	createObjects();

	// UI 생성
	createUI();

	// 타이머 추가
	initTimer();

}

void Scene::Destroy()
{
	for (auto iter : _actors)
	{
		iter->Destroy();
		SAFE_DELETE(iter);
	}
	_actors.clear();

	_ui->Destroy();
	SAFE_DELETE(_ui);
}

void Scene::Update(float deltatime)
{
	for (auto iter : _actors)
	{
		iter->Update(deltatime);
	}

	for (auto iter : _reserveRemove)
	{
		RemoveActor(iter);
	}
	_reserveRemove.clear();

	for (auto iter : _reserveAdd)
	{
 		AddActor(iter);
	}
	_reserveAdd.clear();
	_ui->Update(deltatime);
}

void Scene::Render(ID2D1RenderTarget* _dxRenderTarget)
{
	auto M = D2D1::Matrix3x2F::Translation(-_camera.pos.x, -_camera.pos.y);
	_dxRenderTarget->SetTransform(M);  // 카메라 적용 (지금은 _camerapos = {0,0})

	for (auto& list : _renderList)
		for (auto* a : list)
			a->Render(_dxRenderTarget); //@TODO카메라 복붙하긴 했는데 좀 이상한거 같음 고쳐야돼 카메라 잠깐 뺴두고 나중에 추가해도 되고

	if (useGrid() && _gridOn) RenderGrid(_dxRenderTarget);

	_dxRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_ui->Render(_dxRenderTarget);
}

void Scene::RemoveActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	if (actor->GetRenderLayer() < 0 || actor->GetRenderLayer() >= RenderLayer::RL_Count)
		return;

	UpdateGrid(actor, actor->GetPos(), Vector{ -1,-1 });

	{
		auto& list = _renderList[actor->GetRenderLayer()];
		auto iter = std::find(list.begin(), list.end(), actor);
		if (iter != list.end())
		{
			list.erase(iter);
		}
	}

	{
		auto iter = _actors.find(actor);
		if (iter != _actors.end())
		{
			_actors.erase(iter);
			actor->Destroy();
			delete actor;
		}
	}
}

void Scene::AddActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	if (actor->GetRenderLayer() < 0 || actor->GetRenderLayer() >= RenderLayer::RL_Count)
		return;

	_actors.insert(actor);
	_renderList[actor->GetRenderLayer()].push_back(actor);
}

void Scene::ReserveRemove(Actor* actor)
{
	if (nullptr == actor)
		return;

	if (_reserveRemove.contains(actor))
		return;

	_reserveRemove.emplace(actor);
}

void Scene::ReserveAdd(Actor* actor)
{
	if (nullptr == actor)
		return;

	if (_reserveAdd.contains(actor))
		return;

	_reserveAdd.emplace(actor);
}

void Scene::RemoveAllActor()
{
	for (int32 i = 0; i < (int32)RenderLayer::RL_Count; ++i)
	{
		_renderList[i].clear();
	}

	_reserveAdd.clear();
	_reserveRemove.clear();

	for (auto iter : _actors)
	{
		RemoveActor(iter);
	}
	_actors.clear();
}

void Scene::RemoveExceptPlayer()
{
	if (_actors.empty())
		return;

	_reserveAdd.clear();
	_reserveRemove.clear();

	stack<Actor*> copy;
	for (auto iter : _actors)
	{
		if (iter->GetRenderLayer() == RenderLayer::RL_Player)
		{
			copy.push(iter);
			continue;
		}

		ReserveRemove(iter);
	}

	if(!copy.empty())
	{
		_actors.insert(copy.top());
		copy.pop();
	}
}

void Scene::CreateGrid()
{
	_gridCountX = GWinSizeX / GridSize;
	_gridCountY = GWinSizeY / GridSize;

	for (int x = 0; x < _gridCountX; x++)
	{
		for (int y = 0; y < _gridCountY; y++)
		{
			Cell cell{ x,y };
			CellInfo data;
			_grid.emplace(std::make_pair(cell, data));
		}
	}
}

void Scene::UpdateGrid(Actor* actor, Vector prevPos, Vector newPos)
{
	if (!useGrid() || _grid.empty()) return;

	Cell prevCell = Cell::ConvertToCell(prevPos, GridSize);
	Cell currCell = Cell::ConvertToCell(newPos, GridSize);

	if (prevCell == currCell)
		return;

	bool Block = false;
	if (actor->GetActorType() == ActorType::AT_Block)
		Block = true;

	{
		auto find = _grid.find(prevCell);

		if (find != _grid.end())
		{
			auto& cellInfo = find->second;

			auto findActor = cellInfo._actorsInCell.find(actor);
			if (findActor != cellInfo._actorsInCell.end())
			{
				cellInfo._actorsInCell.erase(findActor);

				if (Block)
					cellInfo.canMoveCell = true;
			}
			else
			{
				OutputDebugString(L"Invalid Grid!!");
			}
		}
	}

	if (currCell.index_X < 0 || currCell.index_X >= _gridCountX || currCell.index_Y < 0 || currCell.index_Y >= _gridCountY)
		return;

	// 현재 셀에는 추가
	
		auto find = _grid.find(currCell);
		if (find != _grid.end())
		{
			// 복사복이 아니라 원본을 수정할거라서 Refrence auto 만들었다
			auto& cellInfo = find->second;	// Cell Info

			// 셀이 관리하고 있는 N개의 액터중에 진짜로 현재 Actor가 있는지 검사
			auto findActor = cellInfo._actorsInCell.find(actor);
			if (findActor != cellInfo._actorsInCell.end())
			{
				OutputDebugString(L"Invalid Grid!!"); //@TODO 경고음 고쳐야 됨 계속 뜸 setPos떄문인지
			}
			else
			{
				cellInfo._actorsInCell.insert(actor);
				if (Block)
					cellInfo.canMoveCell = false;
			}
		}
}

void Scene::RenderGrid(ID2D1RenderTarget* _dxRenderTarget)
{
	int32 width = _gridCountX * GridSize;
	int32 height = _gridCountY * GridSize;

	auto brush = ResourceManager::GetInstance()->GetBrush(BrushColor::Red);

	// 가로선 그리기
	for (int y = 0; y <= height; y += GridSize)
	{
		Vector renderPos1 =(Vector((float)0, (float)y));
		Vector renderPos2 = (Vector((float)width, (float)y));

		D2D1_POINT_2F start = D2D1::Point2F(renderPos1.x, renderPos1.y);
		D2D1_POINT_2F end = D2D1::Point2F(renderPos2.x, renderPos2.y);
		_dxRenderTarget->DrawLine(start, end, brush, 1.0f);
	}

	// 세로선 그리기
	for (int x = 0; x <= width; x += GridSize)
	{
		Vector renderPos1 =(Vector((float)x, (float)0));
		Vector renderPos2 = (Vector((float)x, (float)height));

		D2D1_POINT_2F start = D2D1::Point2F(renderPos1.x, renderPos1.y);
		D2D1_POINT_2F end = D2D1::Point2F(renderPos2.x, renderPos2.y);
		_dxRenderTarget->DrawLine(start, end, brush, 1.0f);
	}
}

const CellInfo& Scene::GetCellinfo(Cell cell)
{
	auto it = _grid.find(cell);

	if ( it != _grid.end())
	{
		return it->second;
	}
	return CellInfo{};
}