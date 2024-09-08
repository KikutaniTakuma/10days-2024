#include "EyeStateComp.h"

void EyeStateComp::Save(nlohmann::json& json) {
	SaveCompName(json);
	json["aimeTime"] = aimTime_;
	json["aimFixedTime"] = aimFixedTime_;
	json["fireTime"] = fireTime_;
}

void EyeStateComp::Load(nlohmann::json& json) {
	aimTime_ = json["aimeTime"].get<float32_t>();
	aimFixedTime_ = json["aimFixedTime"].get<float32_t>();
	fireTime_ = json["fireTime"].get<float32_t>();
}

float32_t EyeStateComp::GetAimTime() const
{
	return aimTime_;
}

float32_t EyeStateComp::GetAimFixedTime() const
{
	return aimFixedTime_;
}

float32_t EyeStateComp::GetFireTime() const
{
	return fireTime_;
}
