#pragma once
#include "Scene.h"
#include "ObjectPool.h"

class Stage;
class Room;

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

    void CreateTear(DirType dir, Vector pos,TearStat stat, Vector playervelocity);
    void RemoveTear(class Tear* tear);

    bool AABBIntersect(const RECT& a, const RECT& b);
    bool ComputeMTVAndDir(const RECT& a, const RECT& b, Vector& outMTV, Vector& outDir);

    void Collide_PlayerVsMonsters(float dt);
    void Collide_PlayerTears(float dt);

    void CreateStage(int32 stage);


private:
    int32 _currStage = 0;
    int32 _currRoom = 0;

    ObjectPool<class Tear> _tearPool;
    vector<class Tear*> _reserveTear;

    class Player* _player = nullptr;

    int32 _stage = 1;	// 현재 진행중인 스테이지 
    int32 _maxMonsterCount = 0;	// 먹어야하는 별이 몇개인지
    int32 _curMonsterCount = 0;
};

