#include "EventComp.h"
#include "ObbComp.h"

void EventComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void EventComp::Load([[maybe_unused]]nlohmann::json& json)
{
}

void EventComp::Debug([[maybe_unused]]const std::string& guiName)
{
#ifdef _DEBUG
	if (ImGui::TreeNode(guiName.c_str())) {
		ImGui::Checkbox("flg", isEvent.data());

		ImGui::TreePop();
	}
#endif // _DEBUG

}
