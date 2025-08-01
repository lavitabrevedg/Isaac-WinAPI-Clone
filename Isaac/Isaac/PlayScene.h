#pragma once
#include "Scene.h"

class Stage;
class Room;

class PlayScene : public Scene
{
	using Super = Scene;
public:
    void Init();
    void Destroy();
    void Update(float deltatime);
    void Render(ID2D1RenderTarget* _dxRenderTarget);

    virtual void loadResources() override;
    virtual void createObjects() override;
    virtual void createUI() override;
    virtual void initTimer() override;

private:
    std::vector<Stage*> stages; // 여러 스테이지
    Stage* currentStage = nullptr;
    Room* currentRoom = nullptr;

    class Player* player = nullptr;
};

