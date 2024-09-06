#include "Direction2DComp.h"

void Direction2DComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void Direction2DComp::Load([[maybe_unused]] nlohmann::json& json)
{

}
