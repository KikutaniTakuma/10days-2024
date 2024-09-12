#include "InputMoveComp.h"
#include "Input/Input.h"

void InputMoveComp::FirstUpdate()
{
#ifdef _DEBUG
	bool isOnImGui = ImGui::GetIO().WantCaptureMouse or ImGui::IsAnyItemHovered();

	if (isOnImGui) {
		return;
	}
#endif // _DEBUG
	Lamb::SafePtr gamepad = Input::GetInstance()->GetGamepad();
	Lamb::SafePtr key = Input::GetInstance()->GetKey();
	Lamb::SafePtr mouse = Input::GetInstance()->GetMouse();

	if (gamepad->PushAnyKey()) {
		isPad_ = true;
	}
	else if (key->PushAnyKey() or mouse->PushAnyKey()) {
		isPad_ = false;
	}

	if (isPad_) {
		direction_.x = gamepad->GetStick(Gamepad::Stick::LEFT).x;
	}
	else {
		if (key->GetKey(DIK_A)) {
			direction_.x = -1.0f;
		}
		else if (key->GetKey(DIK_D)) {
			direction_.x = 1.0f;
		}
		else {
			direction_.x = 0.0f;
		}

		direction_ = direction_.Normalize();
	}

	moveVector_ = direction_ * speed_;
}

void InputMoveComp::Debug([[maybe_unused]] const std::string& guiName)
{
#ifdef _DEBUG


	if (ImGui::TreeNode(guiName.c_str())) {

		ImGui::DragFloat("横移動速度", &speed_, 0.05f);

		ImGui::TreePop();
	}

#endif // _DEBUG
}

void InputMoveComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
	json["speed"] = speed_;
}

void InputMoveComp::Load(nlohmann::json& json)
{
	speed_ = json["speed"].get<float32_t>();
}
