#include "JumpComp.h"

void JumpComp::FirstUpdate()
{

	if (isJump_) {
		jumpTime_ += object_.GetDeltaTime();

		if (jumpTime_ > endJumpTime_) {
			jumpTime_ = endJumpTime_;
			isJump_ = false;
		}

	}

}

void JumpComp::Start()
{

	jumpTime_ = 0.0f;
	isJump_ = true;

}

void JumpComp::Stop()
{
	jumpTime_ = endJumpTime_;
}

void JumpComp::Debug([[maybe_unused]] const std::string& guiName)
{

	if (ImGui::TreeNode(guiName.c_str())) {
		
		ImGui::DragFloat("ジャンプ時間", &endJumpTime_, 0.001f);
		ImGui::DragFloat("ジャンプ力", &jumpVelocity_, 0.01f);

		ImGui::TreePop();
	}

}

void JumpComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void JumpComp::Load([[maybe_unused]] nlohmann::json& json)
{
}
