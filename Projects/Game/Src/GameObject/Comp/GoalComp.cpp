#include "GoalComp.h"

void GoalComp::Init()
{
}

void GoalComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void GoalComp::Load([[maybe_unused]] nlohmann::json& json) {

}

