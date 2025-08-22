#pragma once
class Actor;

struct Camera {
	Vector pos{ 0,0 };
	D2D1::Matrix3x2F View() const {
		return D2D1::Matrix3x2F::Translation(-pos.x, -pos.y);
	}
};

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init();
	virtual void Destroy();

	virtual void Update(float deltatime);
	virtual void Render(ID2D1RenderTarget* _dxRenderTarget);

	virtual bool useGrid() const { return false; }

	virtual void loadResources() abstract;
	virtual void createObjects() abstract;
	virtual void createUI() abstract;
	virtual void initTimer() abstract;

	Vector GetCameraPos() { return _camera.pos; }
	void SetCameraPos(Vector pos) { _camera.pos = pos; }

	void RemoveActor(Actor* actor);
	void AddActor(Actor* actor);

	void ReserveRemove(Actor* actor);
	void ReserveAdd(Actor* actor);
	void RemoveAllActor();
	void RemoveExceptPlayer();

	void CreateGrid();
	void UpdateGrid(Actor* actor,Vector prevPos, Vector newPos);
	void RenderGrid(ID2D1RenderTarget* _dxRenderTarget);

	const CellInfo& GetCellinfo(Cell cell);

	bool IsRenderGrid() { return _gridOn; }

protected:
	bool _gridOn = true;
	unordered_set<Actor*> _actors;
	vector<class Actor*> _renderList[RenderLayer::RL_Count];

	unordered_set<Actor*> _reserveAdd;
	unordered_set<Actor*> _reserveRemove;

	map<Cell, CellInfo> _grid;
	int32 _gridCountX;
	int32 _gridCountY;

	Camera _camera;

	//UIManager _ui; @TODO 추가한 후 ui.넣어줘야함
};

