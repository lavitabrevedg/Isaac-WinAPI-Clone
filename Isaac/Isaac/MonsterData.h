#pragma once
#include "DataObject.h"

class MonsterData : public DataObject
{
public:
	MonsterData() {};
	~MonsterData() {};

	wstring GetFileName() override;
	void Load(const json& data) override;
};

