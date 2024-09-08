#include "PlayerComp.h"
#include "TransformComp.h"
#include "SpriteRenderComp.h"
#include "InputMoveComp.h"
#include "FallComp.h"
#include "ObbPushComp.h"
#include "FlagComp.h"

void PlayerComp::Init() {

	transform_ = object_.AddComp<TransformComp>();
	sprite_ = object_.AddComp<SpriteRenderComp>();
	move_ = object_.AddComp<InputMoveComp>();
	fall_ = object_.AddComp<FallComp>();
	collision_ = object_.AddComp<ObbPushComp>();
	isDead_ = object_.AddComp<FlagComp>();	

}

void PlayerComp::FirstUpdate() {

}

void PlayerComp::Move() {

	transform_->translate += move_->GetMoveVector();

	if (not collision_->GetObbComp().GetIsCollision() and not fall_->GetIsFall()) {
		fall_->Start();
		fall_->gravity = -0.98f;
	}
	
	if(collision_->GetObbComp().GetIsCollision().OnStay()) {
		fall_->Stop();
	}

	transform_->translate.y += fall_->GetFall();


}

void PlayerComp::Event() {

	if (collision_->GetObbComp().GetIsCollision().OnEnter()) {
		fall_->Stop();
	}

}

void PlayerComp::Update() {

}

void PlayerComp::LastUpdate() {

}

void PlayerComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void PlayerComp::Load([[maybe_unused]] nlohmann::json& json) {

}

void PlayerComp::SetIsBeamCollision(const Lamb::Flg& collisionFlg)
{
	beamCollisionFlg_ = collisionFlg;
}
