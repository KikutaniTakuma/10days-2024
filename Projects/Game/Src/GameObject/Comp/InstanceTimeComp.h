#pragma once
#include "../Object.h"
class InstanceTimeComp : public IComp {
public:
	using IComp::IComp;

	~InstanceTimeComp() = default;

public:
	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	void FirstUpdate() override;

	float32_t GetInstanceTime() const;

	void Debug(const std::string& guiName) override;

public:
	float32_t instanceTime_ = 0.0f;
};
