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
#include "Input/Input.h"

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

	Lamb::SafePtr gamepad = Input::GetInstance()->GetGamepad();
	Lamb::SafePtr key = Input::GetInstance()->GetKey();
	Lamb::SafePtr mouse = Input::GetInstance()->GetMouse();

	transform_->translate += move_->GetMoveVector();

	if (fabsf(move_->GetDirection().Length()) > 0.01f) {
		direction_->direction_ = { move_->GetMoveVector().x, move_->GetMoveVector().y };
	}

	if (not OnGround() and not fall_->GetIsFall()) {
		fall_->Start();
	}

	transform_->translate.y += fall_->GetFall();

	if (OnGround() && collision_->GetObbComp().GetIsCollision().OnStay()) {
		fall_->Stop();
	}

	//雲が10未満でRボタンかトリガーを押したら食事開始。吐き出す動作とは重複しない
	if (not eatCloud_->isEat_ and count_->GetCount() < 10 and OnGround() and
		not gamepad->Pushed(Gamepad::Button::LEFT_SHOULDER) and not gamepad->Pushed(Gamepad::Trigger::LEFT) and
		(gamepad->Pushed(Gamepad::Button::RIGHT_SHOULDER) or gamepad->Pushed(Gamepad::Trigger::RIGHT))) {

		eatCloud_->isEat_ = true;

	}

	//雲を持っていてLボタンかトリガーを押したら吐き出し開始。食べる動作とは重複しない
	if (not removeCloud_->isRemove_ and count_->GetCount() > 0 and OnGround() 
		and (gamepad->Pushed(Gamepad::Button::LEFT_SHOULDER) or gamepad->Pushed(Gamepad::Trigger::LEFT)) and
		not gamepad->Pushed(Gamepad::Button::RIGHT_SHOULDER) and not gamepad->Pushed(Gamepad::Trigger::RIGHT)) {

		removeCloud_->isRemove_ = true;

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
