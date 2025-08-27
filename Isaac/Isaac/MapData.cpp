#include "pch.h"
#include "MapData.h"

wstring MapData::GetFileName()
{
	return L"StageData.json";
}

void MapData::Load(const json& data)
{
	constexpr const char* kKeys[DIR_MAX] = { "left", "right", "up", "down" };
	for (auto s : data["stages"])
	{
		StageInfo si;
		si.id = s["id"];
		si.startRoom = s["startRoom"];
		si.bossRoom = s["bossRoom"];
		si.itemRoom = s["itemRoom"];

		for (auto r : s["rooms"])
		{
			RoomInfo ri;
			ri.id = r["id"];
			ri.MapPath = r["MapPath"];
			ri.monsterCount = r["monsterCount"];

			const auto& nb = r.at("neighbor"); 
			for (int i = 0; i < DIR_MAX; ++i)
				ri.neighbor[i] = nb.value(kKeys[i], -1);   // 키 없으면 -1
			si.rooms.emplace(ri.id, ri);
		}
		_stages.emplace(si.id, si);
	}
}
