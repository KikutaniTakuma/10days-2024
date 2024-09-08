#include "JumpComp.h"

void JumpComp::FirstUpdate()
{

	if (count_ > 0) {
		count_--;
	}

}

void JumpComp::Start()
{

	count_ = jumpTime_;

}

void JumpComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void JumpComp::Load([[maybe_unused]] nlohmann::json& json)
{
}
