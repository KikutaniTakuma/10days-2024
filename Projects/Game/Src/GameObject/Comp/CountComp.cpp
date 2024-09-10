#include "CountComp.h"

void CountComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void CountComp::Load([[maybe_unused]]nlohmann::json& json)
{
}
