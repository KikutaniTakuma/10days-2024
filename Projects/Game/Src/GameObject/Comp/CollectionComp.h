#pragma once
#include "../Object.h"

class CollectionComp : public IComp {
public:

	using IComp::IComp;

	~CollectionComp() = default;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

};
