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

		//ターゲットの座標が範囲内なら追従
		if (targetTransform_->translate.x > min_.x and max_.x > targetTransform_->translate.x) {
			transform_->translate.x = targetTransform_->translate.x;
		}
		else if(targetTransform_->translate.x <= min_.x) {
			transform_->translate.x = min_.x;
		}
		else {
			transform_->translate.x = max_.x;
		}

		////ターゲットの座標が範囲内なら追従
		//if (targetTransform_->translate.y > min_.y and max_.y > targetTransform_->translate.y) {
		//	transform_->translate.y = targetTransform_->translate.y;
		//}
		//else if (targetTransform_->translate.y <= min_.y) {
		//	transform_->translate.y = min_.y;
		//}
		//else {
		//	transform_->translate.y = max_.y;
		//}

	}

}

void FollowCamera2DComp::SetPlayerComp(PlayerComp* playerComp)
{

	target_ = playerComp;
	if (target_.empty()) {
		return;
	}

	targetTransform_ = target_->getObject().GetComp<TransformComp>();

}

void FollowCamera2DComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void FollowCamera2DComp::Load([[maybe_unused]] nlohmann::json& json) {

}

