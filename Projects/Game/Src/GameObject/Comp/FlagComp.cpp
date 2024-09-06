#include "FlagComp.h"

void FlagComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void FlagComp::Load([[maybe_unused]] nlohmann::json& json) {

}

