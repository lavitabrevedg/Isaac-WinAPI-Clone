#pragma once
#include "DataObject.h"

struct RoomInfo
{

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

