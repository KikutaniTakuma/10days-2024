#pragma once

#include "../Object.h"
#include "Utils/Easeing.h"

class EaseingComp : public IComp {
public:
	using IComp::IComp;

	~EaseingComp() = default;

	void Init() override;

	void Finalize() override;

	void LastUpdate();

	void Debug(const std::string& guiName) override;

public:
	Easeing& GetEaseing();

public:
	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

public:
	bool isLoop;

	float spdT = 0.0f;

	Easeing::Type type = Easeing::Type::kNone;
private:
	std::unique_ptr<Easeing> ease_;
};
