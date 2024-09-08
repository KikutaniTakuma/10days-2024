#include "CollectionComp.h"

void CollectionComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void CollectionComp::Load([[maybe_unused]] nlohmann::json& json) {

}

