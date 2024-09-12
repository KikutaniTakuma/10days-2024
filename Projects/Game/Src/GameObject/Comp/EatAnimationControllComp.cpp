#include "EatAnimationControllComp.h"

void EatAnimationControllComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void EatAnimationControllComp::Load([[maybe_unused]]nlohmann::json& json) {

}

void EatAnimationControllComp::Load() {

}

void EatAnimationControllComp::Init() {

}

void EatAnimationControllComp::SetIsLeft(bool isLeft)
{
}

void EatAnimationControllComp::StartAnimation()
{
}
