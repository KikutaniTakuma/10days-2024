#include "CloudRenderComp.h"
#include "SpriteRenderDataComp.h"
#include "Utils/Random.h"
#include "EaseingComp.h"
#include "TransformComp.h"
#include "InstanceTimeComp.h"
#include "CloudComp.h"

void CloudRenderComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
	json["startTime_Max"] = randDuration_.max;
	json["startTime_Min"] = randDuration_.min;
	json["scaleMax"] = scaleMax_;
}

void CloudRenderComp::Load([[maybe_unused]]nlohmann::json& json) {
	if (json.contains("startTime_Max") and json.contains("startTime_Min") and json.contains("scaleMax")) {

	randDuration_.max = json["startTime_Max"].get<float32_t>();
	randDuration_.min = json["startTime_Min"].get<float32_t>();
	scaleMax_ = json["scaleMax"].get<float32_t>();
	}
}

void CloudRenderComp::Load() {
	scale_ = Vector3::kIdentity;
}

void CloudRenderComp::Init() {
	spriteRenderDataComp_ = object_.AddComp<SpriteRenderDataComp>();
	easeingComp_ = object_.AddComp<EaseingComp>();

	transformComp_ = object_.AddComp<TransformComp>();
	instanceTimeComp_ = object_.AddComp<InstanceTimeComp>();
	easeStartTime_ = Lamb::Random(randDuration_.min, randDuration_.max);

	cloudComp_ = object_.AddComp<CloudComp>();
}

void CloudRenderComp::FirstUpdate()
{
	if (not isFirstUpdate_) {
		spriteRenderDataComp_->uvTransform.scale.x = 1.0f / 4.0f;
		spriteRenderDataComp_->uvTransform.translate.x = 1.0f / 4.0f * static_cast<float>(Lamb::Random(0u, 3u));

		isFirstUpdate_ = true;
	}
}

void CloudRenderComp::Update() {
	if (easeStartTime_ <= instanceTimeComp_->GetInstanceTime() and not easeingComp_->GetEaseing().GetIsActive()) {
		easeingComp_->GetEaseing().Start(easeingComp_->isLoop, easeingComp_->spdT, easeingComp_->type);
	}

	playertTouchEase_.Update();

	if (cloudComp_->GetIsHitPlayer().OnEnter()) {
		playertTouchEase_.Start(false, playertTouchEaseTime_, Easeing::Type::kOutElastic);
	}

}

void CloudRenderComp::LastUpdate() {
	if (playertTouchEase_.GetIsActive()) {
		spriteRenderDataComp_->userOffsetTransform.scale = playertTouchEase_.Get(scale_ * scaleMax_, scale_);
	}
	else if (easeingComp_->GetEaseing().GetIsActive()) {
		spriteRenderDataComp_->userOffsetTransform.scale = easeingComp_->GetEaseing().Get(scale_, scale_ * scaleMax_);
	}
}

void CloudRenderComp::Debug([[maybe_unused]]const std::string& guiName)
{
#ifdef _DEBUG
	if(ImGui::TreeNode(guiName.c_str())){
		if (ImGui::Button("雲ランダム")) {
			spriteRenderDataComp_->uvTransform.scale.x = 1.0f / 4.0f;
			spriteRenderDataComp_->uvTransform.translate.x = 1.0f / 4.0f * static_cast<float>(Lamb::Random(0u, 3u));
		}
		ImGui::DragFloat2("拡縮開始時間ランダム倍率", randDuration_.data(), 0.001f, 0.0f, 1.0f);
		ImGui::DragFloat("拡縮最大倍率", &scaleMax_, 0.001f, 0.0f, 2.0f);
		ImGui::DragFloat3("スケール", scale_.data(), 0.01f, 0.0f, 10000.0f);

		ImGui::TreePop();
	}
#endif // _DEBUG

}
