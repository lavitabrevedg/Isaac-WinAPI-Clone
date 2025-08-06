#pragma once

struct Cell
{
public:
	Vector _pos;
	vector<class Actor*> _inactor;
};

class Grid
{
public:
	void Init(int xCells, int yCells, int GridSize);
	//void Update(float deltaTime, class Player* player, vector<class Enemy*> enemy, vector<class EnemyBullet*> enemybu, vector<class Bullet*> bullet);
	void Render(HDC hdc);
	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);
	void Update(Actor* obj);

	int GetCellx() { return _xCells; }
	int GetCelly() { return _yCells; }
	vector<vector<Cell*>> Getcells() { return _cells; }

	Cell* GetCellFromWorldPos(Vector Actorpos);

private:
	vector<vector<Cell*>> _cells;
	int _cellSize = 0;
	int _xCells;
	int _yCells;
};

