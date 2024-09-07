#pragma once
#include "../Object.h"

class JumpComp : public IComp {
public:

	using IComp::IComp;

	~JumpComp() = default;

	void FirstUpdate() override;

	void Start();

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	float32_t jumpVelocity_ = 10.0f;

};

