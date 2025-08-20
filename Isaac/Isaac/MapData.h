#pragma once
#include "DataObject.h"

struct RoomInfo
{
	int32 id; //11 21 31 스테이지,룸id
	string tileMapPath;
	int32 monsterCount;
	int32 startX;
	int32 startY;
	int32 linkStage;
};

class MapData : public DataObject
{
public:
	MapData() {}
	virtual ~MapData() {}

	wstring GetFileName() override;
	void Load(const json& data)override;

	std::map<int32, RoomInfo> _stage;
};

