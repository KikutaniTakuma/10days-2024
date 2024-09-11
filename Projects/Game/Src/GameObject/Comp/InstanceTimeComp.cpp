#include "InstanceTimeComp.h"
#include <format>


void InstanceTimeComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void InstanceTimeComp::Load([[maybe_unused]]nlohmann::json& json)
{
}

void InstanceTimeComp::FirstUpdate() {
	instanceTime_ += object_.GetDeltaTime();
}

float32_t InstanceTimeComp::GetInstanceTime() const
{
	return instanceTime_;
}

void InstanceTimeComp::Debug([[maybe_unused]]const std::string& guiName) {
#ifdef _DEBUG
	if (ImGui::TreeNode(guiName.c_str())) {
		ImGui::Text(std::format("instance time : {}", instanceTime_).c_str());

		
		ImGui::TreePop();
	}
#endif // _DEBUG

}
