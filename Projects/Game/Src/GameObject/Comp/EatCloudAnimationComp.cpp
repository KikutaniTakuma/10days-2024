#include "EatCloudAnimationComp.h"
#include "TransformComp.h"
#include "SpriteRenderDataComp.h"
#include "SpriteRenderComp.h"

void EatCloudAnimationComp::Init() {
	transformComp_ = object_.AddComp<decltype(transformComp_)::type>();
	spriteRenderDataComp_ = object_.AddComp<decltype(spriteRenderDataComp_)::type>();
	spriteRenderComp_ = object_.AddComp<decltype(spriteRenderComp_)::type>();

	scaleMagnification_.min = 1.0f;
	scaleMagnification_.max = 2.0f;

	colorAlphaMagnification_.min = 0.0f;
	colorAlphaMagnification_.max = 1.0f;

	spriteRenderComp_->isDraw = false;
}

void EatCloudAnimationComp::PullStart() {
	isReturnTime_ = false;
	ease_.Start(false, pullTime_, pullType_);
	spriteRenderDataComp_->color.color.a = 1.0f;
	isClorEaseStart_ = false;
	spriteRenderComp_->isDraw = true;
}

void EatCloudAnimationComp::ReturnStart() {
	ease_.Start(false, returnTime_, returnType_);
	isReturnTime_ = true;
}

void EatCloudAnimationComp::FirstUpdate() {
	if (not isFirstUpdate_) {
		defaultScale_ = transformComp_->scale.x;
		isFirstUpdate_ = true;
		spriteRenderDataComp_->type = BlendType::kNormal;
	}
}

void EatCloudAnimationComp::Update() {
	if (ease_.GetIsActive()) {
		if (not isReturnTime_) {
			transformComp_->scale.x = defaultScale_ * ease_.Get(scaleMagnification_.min, scaleMagnification_.max);
		}
		else {
			transformComp_->scale.x = defaultScale_ * ease_.Get(scaleMagnification_.max, scaleMagnification_.min);
		}
	}
	else {
		transformComp_->scale.x = defaultScale_;
	}

	if (colorEase_.GetIsActive()) {
		spriteRenderDataComp_->color.color.a = colorEase_.Get(colorAlphaMagnification_.max, colorAlphaMagnification_.min);
	}
	else if(isClorEaseStart_){
		spriteRenderDataComp_->color.color.a = colorAlphaMagnification_.min;
		spriteRenderComp_->isDraw = false;
	}

	if (isReturnTime_ and colorEaseStartT < ease_.GetT() and not isClorEaseStart_) {
		colorEase_.Start(false, returnTime_ * 0.5f);
		isClorEaseStart_ = true;
	}
}

void EatCloudAnimationComp::LastUpdate() {

	ease_.Update();
	colorEase_.Update();
	if (ease_.GetIsActive().OnExit() and not isReturnTime_) {
		ReturnStart();
	}
}

void EatCloudAnimationComp::SetIsLeft(bool isLeft) {
	if (isLeft) {
		transformComp_->translate.x = std::abs(transformComp_->translate.x) * -1.0f;
		spriteRenderDataComp_->offsetType = SpriteRenderDataComp::Offset::kLeft;
	}
	else {
		transformComp_->translate.x = std::abs(transformComp_->translate.x);
		spriteRenderDataComp_->offsetType = SpriteRenderDataComp::Offset::kRight;
	}
}

void EatCloudAnimationComp::Debug([[maybe_unused]]const std::string& guiName) {
	if (ImGui::TreeNode(guiName.c_str())) {
		ImGui::DragFloat("引っ張る時間", &pullTime_, 0.001f, 0.0f, 1.0f);
		ImGui::DragFloat("戻る時間", &returnTime_, 0.001f, 0.0f, 1.0f);

		if (ImGui::Button("start")) {
			PullStart();
		}

		ImGui::TreePop();
	}
}

Lamb::SafePtr<class TransformComp> EatCloudAnimationComp::GetTransformComp()
{
	return transformComp_;
}

Lamb::SafePtr<class SpriteRenderDataComp> EatCloudAnimationComp::GetSpriteRenderDataComp()
{
	return spriteRenderDataComp_;
}

void EatCloudAnimationComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void EatCloudAnimationComp::Load([[maybe_unused]]nlohmann::json& json) {
}
