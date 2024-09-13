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
				transform_->translate.x = startX_ - moveValue_;
			}

			isStickUsed_ = true;

		}

		if (transform_->translate.x < startX_) {

			transform_->translate.x += backValue_;

			if (transform_->translate.x > startX_) {
				transform_->translate.x = startX_;
			}

		}

	}
	else {

		if ((gamepad->Pushed(Gamepad::Button::RIGHT) or
			(gamepad->GetStick(Gamepad::Stick::LEFT).x > 0.0f) or
			key->Pushed(DIK_D) or key->Pushed(DIK_RIGHT))) {

			if (not isStickUsed_) {
				transform_->translate.x = startX_ + moveValue_;
			}

			isStickUsed_ = true;

		}
		else {
			isStickUsed_ = false;
		}

		if (transform_->translate.x > startX_) {

			transform_->translate.x -= backValue_;

			if (transform_->translate.x < startX_) {
				transform_->translate.x = startX_;
			}

		}

	}

}

void ArrowComp::Debug([[maybe_unused]] const std::string& guiName)
{

#ifdef _DEBUG

	if (ImGui::TreeNode(guiName.c_str())) {
		ImGui::DragFloat("初期X座標", &startX_, 0.01f);
		ImGui::DragFloat("移動量", &moveValue_, 0.01f);
		ImGui::DragFloat("戻るスピード", &backValue_, 0.01f);
		ImGui::Checkbox("右か左か", &isLeft_);
		ImGui::TreePop();
	}

#endif // _DEBUG


}

void ArrowComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
	json["isLeft"] = isLeft_;
	json["startX"] = startX_;
	json["moveValue"] = moveValue_;
	json["backValue"] = backValue_;
}

void ArrowComp::Load([[maybe_unused]] nlohmann::json& json)
{
	isLeft_ = json["isLeft"].get<bool>();
	startX_ = json["startX"].get<bool>();
	moveValue_ = json["moveValue"].get<bool>();
	backValue_ = json["backValue"].get<bool>();
}
