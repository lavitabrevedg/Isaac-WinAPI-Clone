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
			ri.monsterCount = r["monsterCount"]; //@TODO json���� �����صд�� ����, gpt�� ���ִ� ��� Stage manager�� �ְ� stage�� ���⼭ ��� �����͵��� ���������� �����ִ´�
			for (int32 i = 0; i < 4; i++)
			{
				ri.neighbor[i] = r["neighbor"].at(i).get<int32>(); //����
			}
			si.rooms.emplace(ri.id, ri);
		}
		_stages.emplace(si.id, si);
	}
}
