#pragma once
#include "DataObject.h"

enum DropItemType
{
	Coin,
	Heart,
	Boom,
	Key,
	Card,
	Pill,
};

class DropItemData : public DataObject
{
public:
	DropItemData() {};
	~DropItemData() {};

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
	string _name;
	string _spritePath;
	int32 _amount;
	DropItemType _itemtype;
};