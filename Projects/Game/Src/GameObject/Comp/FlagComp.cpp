#include "FlagComp.h"

void FlagComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void FlagComp::Load([[maybe_unused]] nlohmann::json& json) {

}

void FlagComp::Debug([[maybe_unused]] const std::string& guiName)
{
#ifdef _DEBUG
	if (ImGui::TreeNode(guiName.c_str())) {
		ImGui::Checkbox("フラグ", isActive_.data());

		ImGui::TreePop();
	}
#endif // _DEBUG
}

