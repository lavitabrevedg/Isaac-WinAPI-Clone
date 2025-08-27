#pragma once
#include "DataObject.h"

//struct ItemStat
//{
//	float damageAdd = 0.f;
//	float damageMul = 1.f;
//	float tearsAdd = 0.f;
//	float tearsMul = 1.f;
//	float shotspeedAdd = 0.f;
//	float shotspeedMul = 1.f;
//};

enum types
{
	Passive,
	Active
};

class ItemData : public DataObject
{
public:
	ItemData() {};
	~ItemData() {};
	wstring GetFileName() override;
	void Load(const json& data) override;

	template<typename T>
	void ConvertEnum(const json& data, const char* name, T& value)
	{
		if (data.contains(name))
		{
			string data_name = data[name];
			auto data_enum = magic_enum::enum_cast<T>(data_name);
			if (data_enum.has_value())
			{
				value = data_enum.value();
			}
		}
	}

	int32 _id;
	string _key;
	string _name;
	types _type;
	string _playercostumePath;
	ItemStat _tearstat;
};

