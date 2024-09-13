#include "StarComp.h"
#include "UITransformComp.h"
#include "UIDrawComp.h"
#include "SpriteRenderDataComp.h"
#include "EaseingComp.h"

void StarComp::Init()
{
	easing_ = object_.AddComp<EaseingComp>();
	spriteRenderDataComp_ = object_.AddComp<SpriteRenderDataComp>();
	UIDraw_ = object_.AddComp<UIDrawComp>();
	UITransform_ = object_.AddComp<UITransformComp>();
}

void StarComp::Update()
{

	if (isEasingStart_) {

		if (easing_->GetEaseing().GetIsActive()) {
			UITransform_->scale = easing_->GetEaseing().Get(startScale_, endScale_);
		}
		else {
			UITransform_->scale = endScale_;
			isEasingEnd_ = true;
		}

	}
	else {

		UITransform_->scale = { 0.0f,0.0f,0.0f };

	}

}

void StarComp::Start()
{

	easing_->isLoop = false;
	easing_->spdT = 0.5f;
	easing_->type = Easeing::Type::kInSine;
	easing_->GetEaseing().Start(easing_->isLoop, easing_->spdT, easing_->type);
	isEasingStart_ = true;

}

void StarComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void StarComp::Load([[maybe_unused]] nlohmann::json& json)
{
}
