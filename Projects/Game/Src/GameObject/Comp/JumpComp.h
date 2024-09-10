#pragma once
#include "../Object.h"

class JumpComp : public IComp {
public:

	using IComp::IComp;

	~JumpComp() = default;

	void FirstUpdate() override;

	void Start();

	void Stop();

	void Debug(const std::string& guiName);

	float32_t GetJumpVelocity() const { return jumpVelocity_ * jumpTime_; }

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	float32_t jumpVelocity_ = 10.0f;

	float32_t jumpTime_ = 0.0_f32;
	float32_t startJumpTime_ = 0.11_f32;
	Lamb::Flg isJump_;

};

