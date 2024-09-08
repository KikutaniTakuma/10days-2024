#pragma once
#include "../Object.h"

class GoalComp : public IComp {
public:

	using IComp::IComp;

	~GoalComp() = default;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

};
