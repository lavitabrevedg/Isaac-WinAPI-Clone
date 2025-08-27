#include "pch.h"
#include "DropItemData.h"

wstring DropItemData::GetFileName()
{
	return L"DropItemData";
}

void DropItemData::Load(const json& data)
{
	_id = data["id"];
	_name = data["name"];
	_spritePath = data["spritePath"];
	_amount = data["amount"];
	//ConvertEnum<DropItemType>(data, "DropItemType", _itemtype);
}
