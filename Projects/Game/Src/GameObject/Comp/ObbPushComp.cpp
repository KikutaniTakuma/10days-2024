#include "ObbPushComp.h"
#include "../Manager/ObbManager.h"

void ObbPushComp::Init()
{
	obbComp_ = object_.AddComp<ObbComp>();
	ObbManager::GetInstance()->Set(this);
}

void ObbPushComp::Finalize() {
	ObbManager::GetInstance()->Erase(this);
}

void ObbPushComp::Collision(Lamb::SafePtr<ObbComp> other) {
	bool isPush = false;

	for (const auto& i : pushTags_) {
		if (other->getObject().HasTag(i)) {
			isPush = true;
			break;
		}
	}

	if (isPush) {
		Vector3 pushvector;
		if (obbComp_->IsCollision(other.get(), pushvector)) {
			other->GetTransformComp().translate += pushvector;
		}
	}
}

void ObbPushComp::SetPushTag(const std::string& pushTag) {
	if (not pushTags_.contains(pushTag)) {
		pushTags_.insert(pushTag);
	}
}

void ObbPushComp::ErasePushTag(const std::string& pushTag) {
	if (pushTags_.contains(pushTag)) {
		pushTags_.erase(pushTag);
	}
}

void ObbPushComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
	json["pushTags"] = nlohmann::json::array();
	for (auto& i : pushTags_) {
		json["pushTags"].push_back(i);
	}
}

void ObbPushComp::Load(nlohmann::json& json)
{
	pushTags_.clear();
	pushTags_.reserve(json["pushTags"].size());
	for (size_t i = 0; i < json["pushTags"].size(); i++) {
		pushTags_.insert(json["pushTags"][i].get<std::string>());
	}
}

void ObbPushComp::Debug([[maybe_unused]]const std::string& guiName)
{
#ifdef _DEBUG
	if(ImGui::TreeNode(guiName.c_str())) {
		ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
		for (auto& i : pushTags_) {
			if (ImGui::Button("erase")) {
				pushTags_.erase(i);
				break;
			}
			ImGui::SameLine();
			ImGui::Text("tag : % s", i.c_str());
		}
		ImGui::EndChild();

		inputTag_.resize(32);
		ImGui::InputText(
			"タグ",
			inputTag_.data(),
			inputTag_.size()
		);
		if (ImGui::Button("タグ追加")) {
			std::string addtag;
			for (auto& i : inputTag_) {
				if (i == '\0') {
					break;
				}
				addtag.push_back(i);
			}
			pushTags_.insert(addtag);
		}

		ImGui::TreePop();
	}
#endif // _DEBUG
}
