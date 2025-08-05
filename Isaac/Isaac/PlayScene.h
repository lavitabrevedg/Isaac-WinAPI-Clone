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

    void CreateTear(DirType dir, Vector pos,TearStat stat, Vector playervelocity);
    void RemoveTear(class Tear* tear);

    bool AABBIntersect(const RECT& a, const RECT& b);

private:
    std::vector<Stage*> stages; // 여러 스테이지
    Stage* currentStage = nullptr;
    Room* currentRoom = nullptr;
    ObjectPool<class Tear> _tearPool;
    vector<class Tear*> _reserveTear;

    class Player* player = nullptr;
};

