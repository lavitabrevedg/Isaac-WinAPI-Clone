#pragma once
#include "DataObject.h"

class DropItemData : public DataObject
{
public:
	DropItemData() {};
	~DropItemData() {};

	wstring GetFileName() override;
	void Load(const json& data) override;
};

