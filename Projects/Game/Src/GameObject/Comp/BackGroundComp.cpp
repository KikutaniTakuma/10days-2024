#include "BackGroundComp.h"
#include "FollowCamera2DComp.h"
#include "TransformComp.h"
#include "PlayerComp.h"
#include "SpriteRenderComp.h"

void BackGroundComp::Init()
{
	transform_ = object_.AddComp<TransformComp>();
	spriteRenderComp_ = object_.AddComp<SpriteRenderComp>();
}

void BackGroundComp::Move()
{

	if (targetTransform_) {

		transform_->translate.x = targetTransform_->translate.x;

	}

}

void BackGroundComp::SetFollowCameraComp(FollowCamera2DComp* followCameraComp)
{

	target_ = followCameraComp;
	if (target_.empty()) {
		return;
	}

	targetTransform_ = target_->getObject().GetComp<TransformComp>();

}

void BackGroundComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void BackGroundComp::Load([[maybe_unused]] nlohmann::json& json) {

}

