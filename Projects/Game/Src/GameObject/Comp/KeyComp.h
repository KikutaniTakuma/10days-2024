#pragma once
#include "../Object.h"

class KeyComp : public IComp {
public:

	using IComp::IComp;

	~KeyComp() = default;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:



};
