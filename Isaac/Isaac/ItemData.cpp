#include "pch.h"
#include "ItemData.h"

wstring ItemData::GetFileName()
{
	return wstring();
}

void ItemData::Load(const json& data)
{
	_id = data["id"];
	_key = data["key"];
	_name = data["name"];
	ConvertEnum<types>(data, "types", _type);
	_playercostumePath = data["playercostumePath"];

	const auto& st = data["Itemstat"];

	_tearstat.damageAdd = st.value("damageAdd", _tearstat.damageAdd);
	_tearstat.damageMul = st.value("damageMul", _tearstat.damageMul);
	_tearstat.tearsAdd = st.value("tearsAdd", _tearstat.tearsAdd);
	_tearstat.tearsMul = st.value("tearsMul", _tearstat.tearsMul);
	_tearstat.shotspeedAdd = st.value("shotspeedAdd", _tearstat.shotspeedAdd);
	_tearstat.shotspeedMul = st.value("shotspeedMul", _tearstat.shotspeedMul);
}
