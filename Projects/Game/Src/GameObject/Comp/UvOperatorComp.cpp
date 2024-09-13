#include "UvOperatorComp.h"
#include "SpriteRenderDataComp.h"

void UvOperatorComp::Init()
{
	spriteRenderDataComp_ = object_.AddComp<SpriteRenderDataComp>();
}

void UvOperatorComp::Move()
{

	if (isStartMove_) {

		spriteRenderDataComp_->uvTransform.translate += moveValue_;

		if (fabsf(spriteRenderDataComp_->uvTransform.translate.x) > 1.0f) {
			spriteRenderDataComp_->uvTransform.translate.x = 0.0f;
		}

		if (fabsf(spriteRenderDataComp_->uvTransform.translate.y) > 1.0f) {
			spriteRenderDataComp_->uvTransform.translate.y = 0.0f;
		}

		if (fabsf(spriteRenderDataComp_->uvTransform.translate.z) > 1.0f) {
			spriteRenderDataComp_->uvTransform.translate.z = 0.0f;
		}

	}

}

void UvOperatorComp::Debug([[maybe_unused]] const std::string& guiName)
{

#ifdef _DEBUG

	if (ImGui::TreeNode(guiName.c_str())) {
		ImGui::DragFloat3("UV移動速度", moveValue_.data(), 0.001f);
		ImGui::Checkbox("UVを動かすか", &isStartMove_);
		ImGui::TreePop();
	}

#endif // _DEBUG


}

void UvOperatorComp::Save(nlohmann::json& json) {
	SaveCompName(json);
	json["moveValue"] = nlohmann::json::array();
	for (auto& i : moveValue_) {
		json["moveValue"].push_back(i);
	}
	json["isMove"] = isStartMove_;
}

void UvOperatorComp::Load([[maybe_unused]] nlohmann::json& json) {
	for (size_t i = 0; i < json["moveValue"].size(); i++) {
		moveValue_[i] = json["moveValue"][i].get<float32_t>();
	}
	isStartMove_ = json["isMove"].get<bool>();
}

