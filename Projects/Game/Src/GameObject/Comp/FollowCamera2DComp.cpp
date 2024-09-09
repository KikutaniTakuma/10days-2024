#include "FollowCamera2DComp.h"
#include "Camera2DComp.h"
#include "TransformComp.h"

void FollowCamera2DComp::Init()
{
	camera_ = object_.AddComp<Camera2DComp>();
	transform_ = object_.AddComp<TransformComp>();
}

void FollowCamera2DComp::Move()
{
}

void FollowCamera2DComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void FollowCamera2DComp::Load([[maybe_unused]] nlohmann::json& json) {

}

