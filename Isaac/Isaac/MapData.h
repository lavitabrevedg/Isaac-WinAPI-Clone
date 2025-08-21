#pragma once
#include "DataObject.h"

struct RoomInfo
{
	int32 id; //101 102 103 스테이지,룸id
	string MapPath;
	int32 monsterCount;
	int32 neighbor[4];
};

struct StageInfo
{
	int32 id;
	int32 startRoom;
	int32 bossRoom;
	int32 itemRoom;
	map<int32, RoomInfo> rooms;
};

class MapData : public DataObject
{
public:
	MapData() {}
	virtual ~MapData() {}

	wstring GetFileName() override;
	void Load(const json& data)override;

	map<int32, StageInfo> _stages;
};

