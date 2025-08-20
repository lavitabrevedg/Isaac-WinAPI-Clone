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
		info.monsterCount = iter["monsterCount"]; //@TODO json파일 저장해둔대로 수정, gpt에 써있는 대로 Stage manager가 있고 stage가 여기서 얻는 데이터들을 방정보들을 갖고있는다
		info.startX = iter[""];
		info.startY = iter[""];
		info.linkStage = iter["linkStage"];
		_stage.emplace(info.id, info);
	}
}
