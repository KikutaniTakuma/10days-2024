#pragma once

#include "../Object.h"
#include "Utils/Easeing.h"

class EaseingComp : public IComp {
public:
	using IComp::IComp;

	~EaseingComp() = default;

	void Init() override;

	void Finalize() override;

public:
	Easeing& GetEaseing();

public:
	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:
	std::unique_ptr<Easeing> ease_;
};
