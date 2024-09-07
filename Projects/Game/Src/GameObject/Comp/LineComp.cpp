#include "LineComp.h"
#include "ObbComp.h"

void LineComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
	json["start"] = nlohmann::json::array();
	for (auto& i : start) {
		json["start"].push_back(i);
	}
	json["end"] = nlohmann::json::array();
	for (auto& i : end) {
		json["end"].push_back(i);
	}
}

void LineComp::Load(nlohmann::json& json)
{
	for (size_t i = 0; i < start.size(); i++) {
		start[i] = json["start"][i].get<float32_t>();
	}
	for (size_t i = 0; i < end.size(); i++) {
		end[i] = json["end"][i].get<float32_t>();
	}
}

void LineComp::FirstUpdate() {
	if (object_.HasComp<TransformComp>()) {
		Lamb::SafePtr transformComp = object_.GetComp<TransformComp>();

		transformComp->translate = Vector3::Lerp(start, end, 0.5f);
		transformComp->scale = { (start - end).Length(), 10.0f, 10.0f };

		Vector3 to = (end - start).Normalize();
#ifdef _DEBUG
		transformComp->eulerRotate = Quaternion::DirectionToDirection(Vector3::kXIdentity, to).ToEuler();
#else
		transformComp->rotate = Quaternion::DirectionToDirection(Vector3::kXIdentity, to);
#endif // _DEBUG

	}
}

void LineComp::Debug([[maybe_unused]]const std::string& guiName)
{
#ifdef _DEBUG
	if(ImGui::TreeNode(guiName.c_str())) {
		ImGui::DragFloat3("start", start.data(), 0.01f);
		ImGui::DragFloat3("end", end.data(), 0.01f);

		ImGui::TreePop();
	}
#endif // _DEBUG

}
