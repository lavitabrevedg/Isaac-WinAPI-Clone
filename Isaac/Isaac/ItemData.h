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
	/*int32 _indexX;
	int32 _indexY;*/
	string _name;
	types _type;
	string _playercostumeKey;
	/*string _playercostumePath;*/ //@TODO 리소스등록 및 playscene에서 load를 여기서 값을 받아서 하면 좋을 것 같다.
	ItemStat _tearstat;
};

