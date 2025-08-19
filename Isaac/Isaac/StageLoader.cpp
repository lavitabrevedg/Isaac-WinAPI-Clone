#include "pch.h"
#include "StageLoader.h"
#include "Scene.h"
#include "Actor.h"
#include "Block.h"
#include "Monster.h"
#include "Tile.h"

int32 StageLoader::Load(Scene* scene, std::wifstream& file)
{
    int32 maxMonster = 0;

    // 이미 추가된 객체들은 싹다 날려버리고, 파일에서 읽은 정보로 씬을 채운다.
    scene->RemoveAllActor();

    std::wstring line;
    while (std::getline(file, line))
    {
        std::wistringstream iss(line);

        int32 actorType;
        iss >> actorType;   // 파일 stream 이 int타입만 읽어서 임시로 actorType int32

        Actor* actor = nullptr;
        switch ((ActorType)actorType)
        {
        case ActorType::AT_Tile:
            actor = new Tile();
            break;
        case ActorType::AT_Monster:
            actor = new Monster();
            maxMonster++;
            break;
        case ActorType::AT_Block:
            actor = new Block();
            break;
        }

        if (actor)
        {
            scene->AddActor(actor);
            actor->LoadActor(iss);
        }
    }

    return maxMonster;
}
