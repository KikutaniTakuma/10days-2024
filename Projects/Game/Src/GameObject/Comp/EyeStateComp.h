#pragma once
#include "../Object.h"
class EyeStateComp : public IComp {
public:
	enum class State {
		kSearch,
		kAim,
		kAimFixed,
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
	float32_t GetAimTime() const;
	float32_t GetAimFixedTime() const;
	float32_t GetFireTime() const;

public:
	// 狙っている時間のカウント
	float32_t aimCount = 0.0f;
	// 狙いを定めて狙いを固定している時間のカウント
	float32_t aimFixedCount = 0.0f;
	// 発射している時間のカウント(この間は当たり判定が発生？)
	float32_t fireCount = 0.0f;

	// 初期の状態は探している状態
	State state = State::kSearch;

private:
	// 狙っている時間
	float32_t aimTime_ = 0.0f;
	// 狙いを定めて狙いを固定している時間
	float32_t aimFixedTime_ = 0.0f;
	// 発射している時間(この時間は当たり判定が発生？)
	float32_t fireTime_ = 0.0f;
};
