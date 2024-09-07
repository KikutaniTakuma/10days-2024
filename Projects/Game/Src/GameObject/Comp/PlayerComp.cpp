#include "PlayerComp.h"
#include "TransformComp.h"
#include "SpriteRenderComp.h"
#include "InputMoveComp.h"
#include "FallComp.h"
#include "ObbPushComp.h"
#include "FlagComp.h"
#include "Direction2DComp.h"
#include "CsvDataComp.h"
#include "EatCloudComp.h"
#include "RemoveCloudComp.h"
#include "CountComp.h"
#include "Mass2DComp.h"
#include "Game/TileName/TileName.h"

void PlayerComp::Init() {

	transform_ = object_.AddComp<TransformComp>();
	sprite_ = object_.AddComp<SpriteRenderComp>();
	move_ = object_.AddComp<InputMoveComp>();
	fall_ = object_.AddComp<FallComp>();
	collision_ = object_.AddComp<ObbPushComp>();
	isDead_ = object_.AddComp<FlagComp>();	
	direction_ = object_.AddComp<Direction2DComp>();
	csvData_ = object_.AddComp<CsvDataComp>();
	eatCloud_ = object_.AddComp<EatCloudComp>();
	removeCloud_ = object_.AddComp<RemoveCloudComp>();
	count_ = object_.AddComp<CountComp>();
	mass_ = object_.AddComp<Mass2DComp>();

}

void PlayerComp::FirstUpdate() {

}

void PlayerComp::Move() {

	transform_->translate += move_->GetMoveVector();

	if (fabsf(move_->GetDirection().Length()) > 0.01f) {
		direction_->direction_ = { move_->GetMoveVector().x, move_->GetMoveVector().y };
	}

	if (not OnGround() and not fall_->GetIsFall()) {
		fall_->Start();
		fall_->gravity = -0.98f;
	}

	transform_->translate.y += fall_->GetFall();

	if (OnGround() && collision_->GetObbComp().GetIsCollision().OnStay()) {
		fall_->Stop();
	}

}

void PlayerComp::Event() {

	if (OnGround()) {
		fall_->Stop();
	}

}

void PlayerComp::Update() {

}

void PlayerComp::LastUpdate() {

}

bool PlayerComp::OnGround()
{

	if ((csvData_->GetNumber(mass_->GetMassX(), mass_->GetMassY() + 1) == static_cast<int32_t>(TileName::kCloud) or
		csvData_->GetNumber(mass_->GetMassX() - 1, mass_->GetMassY() + 1) == static_cast<int32_t>(TileName::kCloud) or
		csvData_->GetNumber(mass_->GetMassX() + 1, mass_->GetMassY() + 1) == static_cast<int32_t>(TileName::kCloud)) and
		collision_->GetObbComp().GetIsCollision().OnStay()) {
		return true;
	}

	return false;

}

void PlayerComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void PlayerComp::Load([[maybe_unused]] nlohmann::json& json) {

}
