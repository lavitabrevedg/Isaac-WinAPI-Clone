#include "pch.h"
#include "Grid.h"
#include "Actor.h"

// 400 800
void Grid::Init(int xCells, int yCells, int GridSize)
{
	_xCells = xCells;
	_yCells = yCells;

	GWinSizeX / _xCells;
	GWinSizeY / _yCells;

	_cells.resize(GWinSizeX / (GWinSizeX / _xCells));

	for (auto& it : _cells)
	{
		it.resize(GWinSizeY / (GWinSizeY / _yCells));
	}

	_cellSize = GridSize;

	for (int i = 0; i < _xCells; i++)
	{
		for (int j = 0; j < _yCells; j++)
		{
			Cell* cell = new Cell();
			cell->_pos = Vector((i * _cellSize) + 20, (j * _cellSize) + 20);
			_cells[i][j] = cell;
		}
	}
}

void Grid::Render(HDC hdc)
{
	DWORD color = RGB(255, 0, 0);
	HPEN pen = ::CreatePen(PS_SOLID, 1, color);
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);

	HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldbrush = (HBRUSH)::SelectObject(hdc, brush);

	for (int i = 0; i < _xCells; i++)
	{
		for (int j = 0; j < _yCells; j++)
		{
			Vector dot = _cells[i][j]->_pos;
			Rectangle(hdc, dot.x - 20, dot.y - 20, dot.x + 20, dot.y + 20);
		}
	}

	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);
	::SelectObject(hdc, oldbrush);
	::DeleteObject(brush);
}

void Grid::AddActor(Actor* actor)
{
	Cell* cell = GetCellFromWorldPos(actor->GetPos());

	if (cell)
	{
		cell->_inactor.push_back(actor);
		actor->SetCellpos(cell->_pos.x, cell->_pos.y);
	}
}

void Grid::RemoveActor(Actor* actor)
{
	Vector Cellpos = actor->GetCellPos();
	Cell* cell = _cells[Cellpos.x][Cellpos.y];
	auto& list = cell->_inactor;
	list.erase(std::remove(list.begin(), list.end(), actor), list.end());
}

void Grid::Update(Actor* actor)
{
	int newcellx = (int)(actor->GetPos().x / _cellSize);
	int newcelly = (int)(actor->GetPos().y / _cellSize);

	if (actor->GetCellPos() != Vector(newcellx, newcelly))
	{
		RemoveActor(actor);
		actor->SetCellpos(newcellx, newcelly);
		AddActor(actor);
	}
}

Cell* Grid::GetCellFromWorldPos(Vector Actorpos)
{
	int cx = (int)(Actorpos.x / _cellSize);
	int cy = (int)(Actorpos.y / _cellSize);

	if (cx < 0 || cy < 0 || cx >= GWinSizeX || cy >= GWinSizeY)
		return nullptr;

	return _cells[cx][cy];
}