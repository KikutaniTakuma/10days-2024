#include "FollowCamera2DComp.h"
#include "Camera2DComp.h"
#include "TransformComp.h"
#include "PlayerComp.h"

void FollowCamera2DComp::Init()
{
	camera_ = object_.AddComp<Camera2DComp>();
	transform_ = object_.AddComp<TransformComp>();
}

void FollowCamera2DComp::Move()
{

	if (target_) {

		

	}

}

void FollowCamera2DComp::SetPlayerComp(PlayerComp* playerComp)
{

	target_ = playerComp;
	if (target_.empty()) {
		return;
	}



}

void FollowCamera2DComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void FollowCamera2DComp::Load([[maybe_unused]] nlohmann::json& json) {

}

