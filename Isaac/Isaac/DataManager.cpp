#include "pch.h"
#include "DataManager.h"
#include "ResourceManager.h"
#include "MapData.h"
#include "MonsterData.h"
#include "ItemData.h"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

void DataManager::Init()
{
    fs::path directory = ResourceManager::GetInstance()->GetResourcePath() / L"Data/";

    // map 
    {
        loadMapDataObject(directory);
    }

    // monster
    /*{
        loadMonsterDataObject(directory);
    }*/

    // itemData
   /* {
        loadItemDataObject(directory);
    }*/
}

void DataManager::Destroy()
{
    for (auto& [key, res] : _data)
    {
        delete res;
    }
    _data.clear();
    SAFE_DELETE(_mapData);
}

int32 DataManager::GetRandomItemId() const
{
    if (_itemIdList.size() == 0)
        return 0;

    int32 randIndx = RandRange(0, (int32)_itemIdList.size() - 1);
    return _itemIdList[randIndx];
}

void DataManager::loadDataObject(fs::path directory, wstring key, DataObject* obj)
{
    if (_data.find(key) != _data.end())
    {
        // 이미 존재하는 키라면 리턴
        return;
    }

    fs::path path = directory / obj->GetFileName();
    std::ifstream file(path.c_str());
    if (!file.is_open())
    {
        MessageBox(nullptr, L"Failed to open JSON file", L"Error", MB_OK);
        return;
    }

    json data = json::parse(file);
    obj->Load(data);

    _data.emplace(key, obj);
}

void DataManager::loadMapDataObject(fs::path directory)
{
    fs::path path = directory / L"StageData.json";
    std::ifstream file(path.c_str());
    if (!file.is_open())
    {
        MessageBox(nullptr, L"Failed to open JSON file", L"Error", MB_OK);
        return;
    }

    json data = json::parse(file);
    _mapData = new MapData();
    _mapData->Load(data);
}

void DataManager::loadMonsterDataObject(fs::path directory)
{
    fs::path path = directory / L"Monster.json";
    std::ifstream file(path.c_str());
    if (!file.is_open())
    {
        MessageBox(nullptr, L"Failed to open JSON file", L"Error", MB_OK);
        return;
    }

    json data = json::parse(file);
    for (auto iter : data["list"])
    {
        int32 id = iter["id"];
        if (id == 0)
            continue;

        MonsterData* data = new MonsterData();
        data->Load(iter);
        _monsterData.emplace(id, data);
    }
}

void DataManager::loadItemDataObject(fs::path directory)
{
    fs::path path = directory / L"ItemData.json";
    std::ifstream file(path.c_str());
    if (!file.is_open())
    {
        MessageBox(nullptr, L"Failed to open JSON file", L"Error", MB_OK);
        return;
    }

    json data = json::parse(file);
    for (auto iter : data["list"])
    {
        int32 id = iter["id"];
        if (id == 0)
            continue;

        ItemData* data = new ItemData();
        data->Load(iter);
        _itemData.emplace(id, data);
        _itemIdList.emplace_back(id);
    }
}

StageInfo* DataManager::GetStageInfo(int32 stageNumber)const
{
    if (_mapData == nullptr)
        return nullptr;

    auto stage = _mapData->_stages.find(stageNumber);
    if (stage != _mapData->_stages.end())
    {
        return &stage->second;
    }
    return nullptr;
}

RoomInfo* DataManager::GetRoomInfo(int32 stageNumber, int32 RoomNumber)const
{
    if (_mapData == nullptr)
        return nullptr;

    auto stage = _mapData->_stages.find(stageNumber);
    if (stage != _mapData->_stages.end())
    {
        auto room = stage->second.rooms.find(RoomNumber);
        if (room != stage->second.rooms.end())
        {
            return &room->second;
        }
    }
    return nullptr;
}