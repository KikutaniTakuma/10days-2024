#include "EyeStateComp.h"

void EyeStateComp::Save(nlohmann::json& json) {
	SaveCompName(json);
	json["aimeTime"] = aimTime;
	json["aimFixedTime"] = aimFixedTime;
	json["fireTime"] = fireTime;
}

void EyeStateComp::Load(nlohmann::json& json) {
	aimTime = json["aimeTime"].get<float32_t>();
	aimFixedTime = json["aimFixedTime"].get<float32_t>();
	fireTime = json["fireTime"].get<float32_t>();
}
