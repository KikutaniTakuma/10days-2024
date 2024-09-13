#include "ArrowComp.h"
#include "UITransformComp.h"
#include "Input/Input.h"


void ArrowComp::Init()
{
	transform_ = object_.AddComp<UITransformComp>();
}

void ArrowComp::Move()
{

	Lamb::SafePtr gamepad = Input::GetInstance()->GetGamepad();
	Lamb::SafePtr key = Input::GetInstance()->GetKey();
	Lamb::SafePtr mouse = Input::GetInstance()->GetMouse();

	if (isLeft_) {

		if ((gamepad->Pushed(Gamepad::Button::LEFT) or
			(gamepad->GetStick(Gamepad::Stick::LEFT).x < 0.0f) or
			key->Pushed(DIK_A) or key->Pushed(DIK_LEFT))) {

			if (not isStickUsed_) {
				
			}

			isStickUsed_ = true;

		}

	}
	else {

		if ((gamepad->Pushed(Gamepad::Button::RIGHT) or
			(gamepad->GetStick(Gamepad::Stick::LEFT).x > 0.0f) or
			key->Pushed(DIK_D) or key->Pushed(DIK_RIGHT))) {

			if (not isStickUsed_) {

			}

			isStickUsed_ = true;

		}

	}

}

void ArrowComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
	json["isLeft"] = isLeft_;
}

void ArrowComp::Load([[maybe_unused]] nlohmann::json& json)
{
	isLeft_ = json["isLeft"].get<bool>();
}
