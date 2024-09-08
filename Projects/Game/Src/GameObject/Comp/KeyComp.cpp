#include "KeyComp.h"

void KeyComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void KeyComp::Load([[maybe_unused]] nlohmann::json& json) {

}

