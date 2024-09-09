#include "InvisibleComp.h"

void InvisibleComp::Init()
{
}

void InvisibleComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void InvisibleComp::Load([[maybe_unused]] nlohmann::json& json) {

}

