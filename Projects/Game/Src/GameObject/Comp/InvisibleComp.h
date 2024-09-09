#pragma once
#include "../Object.h"

class InvisibleComp : public IComp {
public:

	using IComp::IComp;

	void Init() override;

	~InvisibleComp() = default;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	

};
