#pragma once
#include "DataObject.h"

class ItemData : public DataObject
{
public:
	ItemData() {};
	~ItemData() {};
	wstring GetFileName() override;
	void Load(const json& data) override;
};

