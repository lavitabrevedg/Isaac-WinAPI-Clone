#include "pch.h"
#include "MapData.h"

wstring MapData::GetFileName()
{
	return L"StageData.json";
}

void MapData::Load(const json& data)
{
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
			ri.monsterCount = r["monsterCount"]; //@TODO json파일 저장해둔대로 수정, gpt에 써있는 대로 Stage manager가 있고 stage가 여기서 얻는 데이터들을 방정보들을 갖고있는다
			for (int32 i = 0; i < 4; i++)
			{
				ri.neighbor[i] = r["neighbor"].at(i).get<int32>(); //오류
			}
			si.rooms.emplace(ri.id, ri);
		}
		_stages.emplace(si.id, si);
	}
}
