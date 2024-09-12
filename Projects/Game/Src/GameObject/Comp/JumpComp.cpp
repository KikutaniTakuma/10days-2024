#include "JumpComp.h"

void JumpComp::FirstUpdate()
{

	if (isJump_) {
		jumpTime_ -= object_.GetDeltaTime();

		if (jumpTime_ < 0.0f) {
			jumpTime_ = 0.0f;
			isJump_ = false;
		}

	}

}

void JumpComp::Start()
{

	jumpTime_ = startJumpTime_;
	isJump_ = true;

}

void JumpComp::Stop()
{
	jumpTime_ = 0.0_f32;
}

void JumpComp::Debug([[maybe_unused]] const std::string& guiName)
{
#ifdef _DEBUG


	if (ImGui::TreeNode(guiName.c_str())) {
		
		ImGui::DragFloat("ジャンプ時間", &startJumpTime_, 0.001f);
		ImGui::DragFloat("ジャンプ力", &jumpVelocity_, 0.01f);

		ImGui::TreePop();
	}
#endif // _DEBUG

}

void JumpComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void JumpComp::Load([[maybe_unused]] nlohmann::json& json)
{
}
