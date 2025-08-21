#pragma once
#include "Singleton.h"
#include "DataObject.h"

class MonsterData;
class ItemData;
class MapData;

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
			// �̹� �����ϴ� Ű��� ����
			return dynamic_cast<T*>(find->second);
		}

		return nullptr;
	}

	const MonsterData* GetMonsterData(int32 key) const
	{
		auto find = _monsterData.find(key);
		if (find != _monsterData.end())
		{
			// �̹� �����ϴ� Ű��� ����
			return find->second;
		}

		return nullptr;
	}

	const ItemData* GetItemData(int32 key) const
	{
		auto find = _itemData.find(key);
		if (find != _itemData.end())
		{
			// �̹� �����ϴ� Ű��� ����
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

private:
	map<wstring, DataObject*>	_data;
	map<int32, MonsterData*>	_monsterData;
	map<int32, ItemData*>		_itemData;
	vector<int32>				_itemIdList;	// ������ ���� ������ ����
	MapData* _mapData;
};
