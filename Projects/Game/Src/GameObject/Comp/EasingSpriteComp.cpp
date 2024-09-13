#include "EasingSpriteComp.h"
#include "SpriteRenderDataComp.h"
#include "SpriteRenderComp.h"
#include "EaseingComp.h"

void EasingSpriteComp::Init()
{
	spriteRenderDataComp_ = object_.AddComp<SpriteRenderDataComp>();
	spriteRender_ = object_.AddComp<SpriteRenderComp>();
	easing_ = object_.AddComp<EaseingComp>();
}

void EasingSpriteComp::Move()
{

	if (easing_->isLoop) {

		if (not easing_->GetEaseing().GetIsActive()) {
			easing_->GetEaseing().Start(easing_->isLoop, easing_->spdT, easing_->type);
		}

	}

}

void EasingSpriteComp::Debug([[maybe_unused]] const std::string& guiName)
{

#ifdef _DEBUG

	if (ImGui::TreeNode(guiName.c_str())) {
		ImGui::DragFloat3("イージング移動開始位置", translateStart_.data(), 0.01f);
		ImGui::DragFloat3("イージング移動終了位置", translateEnd_.data(), 0.01f);
		ImGui::DragFloat3("イージングサイズ最小", scaleStart_.data(), 0.01f);
		ImGui::DragFloat3("イージングサイズ最大", scaleEnd_.data(), 0.01f);
		ImGui::TreePop();
	}

#endif // _DEBUG


}

void EasingSpriteComp::Save(nlohmann::json& json) {
	SaveCompName(json);
	json["moveValue"] = nlohmann::json::array();
	for (auto& i : translateStart_) {
		json["moveValue"].push_back(i);
	}
}

void EasingSpriteComp::Load([[maybe_unused]] nlohmann::json& json) {
	for (size_t i = 0; i < json["moveValue"].size(); i++) {
		translateStart_[i] = json["moveValue"][i].get<float32_t>();
	}
}

