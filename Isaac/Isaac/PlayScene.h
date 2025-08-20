#pragma once
#include "Scene.h"
#include "ObjectPool.h"

class Stage;

namespace EffectAnim
{
    inline constexpr AnimInfo tearEffect = { 0,0,4,3,false,0.1f };
}

class PlayScene : public Scene
{
	using Super = Scene;
public:
    PlayScene();
    ~PlayScene();
    void Init();
    void Destroy();
    void Update(float deltatime);
    void Render(ID2D1RenderTarget* _dxRenderTarget);

    static PlayScene* GetGameScene();

    void loadResources() override;
    void createObjects() override;
    void createUI() override;
    void initTimer() override;

    bool useGrid() const override { return true; }

    bool CanMove(const Cell* cell);

    void CreateTear(DirType dir, Vector pos,TearStat stat, Vector playervelocity);
    void RemoveTear(class Tear* tear);

    Vector AABBOverlapLength(const RECT& a, const RECT& b);

    void Collide_Player(float dt);
    void Collide_PlayerTears(float dt);

    void CreateStage(int32 stage);

    Vector GetPlayerPos();

    int Heuristic(Cell curr, Cell end)
    {
        return (abs(end.index_X - curr.index_X) + abs(end.index_Y - curr.index_Y)) * 10;
    }
    bool FindPath(Cell start, Cell end, vector<Cell>& findPath, int32 maxDepth = 10);

    void SpawnEffect(Vector pos, string sprite, int32 width, int32 heigh, AnimInfo info);

    void Clear_Stage();

    bool IsRenderGrid() { return _gridOn; }

private:
    ObjectPool<class Tear> _tearPool;
    vector<class Tear*> _reserveTear;

    class Player* _player = nullptr;

    int32 _stage = 1;	// 현재 진행중인 스테이지 
    int32 _maxMonsterCount = 0;
    int32 _curMonsterCount = 0;

    //Stage _stage;
};

