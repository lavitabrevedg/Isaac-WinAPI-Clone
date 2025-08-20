#include "pch.h"
#include "MapData.h"

wstring MapData::GetFileName()
{
	return L"MapData.json";
}

void MapData::Load(const json& data)
{
	for (auto iter : data["list"])
	{
		RoomInfo info;
		info.id = iter["id"];
		info.tileMapPath = iter["tileMapPath"];
		info.monsterCount = iter["monsterCount"]; //@TODO json���� �����صд�� ����, gpt�� ���ִ� ��� Stage manager�� �ְ� stage�� ���⼭ ��� �����͵��� ���������� �����ִ´�
		info.startX = iter[""];
		info.startY = iter[""];
		info.linkStage = iter["linkStage"];
		_stage.emplace(info.id, info);
	}
}
