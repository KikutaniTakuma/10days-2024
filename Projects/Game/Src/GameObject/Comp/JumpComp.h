#pragma once
#include "../Object.h"

class JumpComp : public IComp {
public:

	using IComp::IComp;

	~JumpComp() = default;

	void FirstUpdate() override;

	void Start();

	float32_t GetJumpVelocity() const { return jumpVelocity_ * float(count_); }

	bool IsStartJump() { return count_ > 0; }

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	float32_t jumpVelocity_ = 1.0f;

	int32_t jumpTime_ = 5;
	int32_t count_ = 0;

};

