#pragma once
#include "../Object.h"

class FollowCamera2DComp : public IComp {
public:

	using IComp::IComp;

	~FollowCamera2DComp() = default;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:



};
