#include "EasingSpriteComp.h"
#include "UISpriteRenderDataComp.h"
#include "UIDrawComp.h"
#include "EaseingComp.h"
#include "UITransformComp.h"

void EasingSpriteComp::Init()
{
	spriteRenderDataComp_ = object_.AddComp<UISpriteRenderDataComp>();
	uiDraw_ = object_.AddComp<UIDrawComp>();
	easing_ = object_.AddComp<EaseingComp>();
	transform_ = object_.AddComp<UITransformComp>();
}

void EasingSpriteComp::Move()
{

	if (not easing_->GetEaseing().GetIsActive()) {
		easing_->GetEaseing().Start(easing_->isLoop, easing_->spdT, easing_->type);
	}

	if (easing_->GetEaseing().GetIsActive()) {
		transform_->translate = easing_->GetEaseing().Get(translateStart_, translateEnd_);
		transform_->scale = easing_->GetEaseing().Get(scaleStart_, scaleEnd_);
		spriteRenderDataComp_->color.color.a = easing_->GetEaseing().Get(transparStart_, transparEnd_);
	}
	else {
		transform_->translate = translateEnd_;
		transform_->scale = scaleEnd_;
		spriteRenderDataComp_->color.color.a = transparEnd_;
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
		ImGui::DragFloat("透明度最大", &transparStart_, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat("透明度最小", &transparEnd_, 0.01f, 0.0f, 1.0f);
		ImGui::TreePop();
	}

#endif // _DEBUG


}

void EasingSpriteComp::Save(nlohmann::json& json) {
	SaveCompName(json);
	json["translateStart"] = nlohmann::json::array();
	for (auto& i : translateStart_) {
		json["translateStart"].push_back(i);
	}
	json["translateEnd"] = nlohmann::json::array();
	for (auto& i : translateEnd_) {
		json["translateEnd"].push_back(i);
	}
	json["scaleStart"] = nlohmann::json::array();
	for (auto& i : scaleStart_) {
		json["scaleStart"].push_back(i);
	}
	json["scaleEnd"] = nlohmann::json::array();
	for (auto& i : scaleEnd_) {
		json["scaleEnd"].push_back(i);
	}
	json["transparStart"] = transparStart_;
	json["transparEnd"] = transparEnd_;
}

void EasingSpriteComp::Load([[maybe_unused]] nlohmann::json& json) {
	for (size_t i = 0; i < json["translateStart"].size(); i++) {
		translateStart_[i] = json["translateStart"][i].get<float32_t>();
	}
	for (size_t i = 0; i < json["translateEnd"].size(); i++) {
		translateEnd_[i] = json["translateEnd"][i].get<float32_t>();
	}
	for (size_t i = 0; i < json["scaleStart"].size(); i++) {
		scaleStart_[i] = json["scaleStart"][i].get<float32_t>();
	}
	for (size_t i = 0; i < json["scaleEnd"].size(); i++) {
		scaleEnd_[i] = json["scaleEnd"][i].get<float32_t>();
	}

	if (json.contains("transparStart")) {
		transparStart_ = json["transparStart"].get<float32_t>();
	}

	if (json.contains("transparEnd")) {
		transparEnd_ = json["transparEnd"].get<float32_t>();
	}
	
}

