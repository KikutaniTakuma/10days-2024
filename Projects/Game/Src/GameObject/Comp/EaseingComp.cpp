#include "EaseingComp.h"

void EaseingComp::Init() {
	ease_ = std::make_unique<Easeing>();
}

void EaseingComp::Finalize() {
	ease_.reset();
}

void EaseingComp::LastUpdate() {
	ease_->Update();
}

void EaseingComp::Debug([[maybe_unused]]const std::string& guiName) {
#ifdef _DEBUG
	if (ImGui::TreeNode(guiName.c_str())) {
		if (ImGui::BeginCombo("BlendType", Easeing::kEaseingTypeString[static_cast<uint32_t>(type)].c_str()))
		{
			for (uint32_t i = 0; i < static_cast<uint32_t>(Easeing::Type::kNum); ++i)
			{
				bool isSelected = (type == static_cast<Easeing::Type>(i));
				if (ImGui::Selectable(Easeing::kEaseingTypeString[i].c_str(), isSelected))
				{
					type = static_cast<Easeing::Type>(i);
				}
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		ImGui::Checkbox("isLoop", &isLoop);
		ImGui::DragFloat("speed", &spdT);
		if (ImGui::Button("Start")) {
			ease_->Start(isLoop, spdT, type);
		}
		else if (ImGui::Button("Stop")) {
			ease_->Stop();
		}


		ImGui::TreePop();
	}
#endif // _DEBUG
}

Easeing& EaseingComp::GetEaseing()
{
	return *ease_;
}

void EaseingComp::Save(nlohmann::json& json) {
	SaveCompName(json);

	json["isLoop"] = isLoop;
	json["spdT"] = spdT;
	json["type"] = Easeing::kEaseingTypeString[static_cast<uint32_t>(type)];
}

void EaseingComp::Load(nlohmann::json& json) {
	isLoop = json["isLoop"].get<bool>();
	spdT = json["spdT"].get<float>();
	std::string typeString = json["type"].get<std::string>();
	for (uint32_t count = 0; auto& i : Easeing::kEaseingTypeString) {
		if (typeString == i) {
			type = static_cast<Easeing::Type>(count);
			break;
		}
		count++;
	}
}
