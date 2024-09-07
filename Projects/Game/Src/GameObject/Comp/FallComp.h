#pragma once

#include "../Object.h"
#include "Drawers/Model/Model.h"

#include "Utils/Flg.h"

class FallComp : public IComp {
public:
	using IComp::IComp;

	~FallComp() = default;

	void FirstUpdate() override;

	float32_t GetFall() {

		//最大値を超えている場合は制限
		if (fabsf(gravity * fallTime_) > fabsf(limit_)) {
			return limit_;
		}

		return gravity * fallTime_;
	}

	void Start();

	void Stop();

	const Lamb::Flg& GetIsFall() const {
		return isFall_;
	}

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

public:
	float32_t gravity = -9.8_f32;
	float32_t limit_ = -9.8f;

private:
	float32_t fallTime_ = 0.0_f32;
	Lamb::Flg isFall_;
};