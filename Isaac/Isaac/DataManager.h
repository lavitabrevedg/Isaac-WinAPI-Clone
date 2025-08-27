#pragma once
#include "Singleton.h"
#include "DataObject.h"

#define MIN_ID 1001
#define MAX_ID 1001

class MonsterData;
class ItemData;
class MapData;
class DropItemData;

class DataManager : public Singleton<DataManager>
{
public:
	DataManager();
	virtual ~DataManager();

	void Init();
	void Destroy() override;

	template<typename T>
	const T* GetData(wstring key) const
	{
		auto find = _data.find(key);
		if (find != _data.end())
		{
			// 이미 존재하는 키라면 리턴
			return dynamic_cast<T*>(find->second);
		}

		return nullptr;
	}

	const MonsterData* GetMonsterData(int32 key) const
	{
		auto find = _monsterData.find(key);
		if (find != _monsterData.end())
		{
			// 이미 존재하는 키라면 리턴
			return find->second;
		}

		return nullptr;
	}

	ItemData* GetItemData(int32 key) const
	{
		auto find = _itemData.find(key);
		if (find != _itemData.end())
		{
			// 이미 존재하는 키라면 리턴
			return find->second;
		}

		return nullptr;
	}

	const DropItemData* GetDroItemData(int32 key) const
	{
		auto find = _dropitemData.find(key);
		if (find != _dropitemData.end())
		{
			return find->second;
		}
		return nullptr;
	}

	int32 GetRandomItemId() const;

	struct StageInfo* GetStageInfo(int32 stageNumber) const;
	struct RoomInfo* GetRoomInfo(int32 stageNumber, int32 RoomNumber) const;

private:
	void loadDataObject(fs::path directory, wstring key, DataObject* obj);

	void loadMapDataObject(fs::path directory);
	void loadMonsterDataObject(fs::path directory);
	void loadItemDataObject(fs::path directory);
	void loadDropItemDataObject(fs::path directory);

private:
	map<wstring, DataObject*>	_data;
	map<int32, MonsterData*>	_monsterData;
	map<int32, ItemData*>		_itemData;
	vector<int32>				_itemIdList;	// 아이템 랜덤 생성을 위함
	MapData* _mapData;
	map<int32, DropItemData*> _dropitemData;
};
