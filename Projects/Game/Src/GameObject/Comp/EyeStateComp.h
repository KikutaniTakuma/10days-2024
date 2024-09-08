#pragma once
#include "../Object.h"
class EyeStateComp : public IComp {
public:
	enum class State {
		kSerch,
		kAim,
		kFire,
		
		kNum
	};

public:
	using IComp::IComp;

	~EyeStateComp() = default;

public:
	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

public:
	// 狙っている時間
	float32_t aimTime = 0.0f;
	// 狙いを定めて狙いを固定している時間
	float32_t aimFixedTime = 0.0f;
	// 発射している時間(この時間は当たり判定が発生？)
	float32_t fireTime = 0.0f;

	// 初期の状態は探している状態
	State state = State::kSerch;
};
