#include "SpriteUVChangeComp.h"
#include "FlagComp.h"
#include "UISpriteRenderDataComp.h"
#include "UITransformComp.h"

void SpriteUVChangeComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void SpriteUVChangeComp::Load([[maybe_unused]]nlohmann::json& json) {
}

void SpriteUVChangeComp::Init() {
	flagComp_ = object_.AddComp<FlagComp>();
	spriteRenderDataComp_ = object_.AddComp<UISpriteRenderDataComp>();
	uiTransformCompComp_ = object_.AddComp<UITransformComp>();
}

void SpriteUVChangeComp::LastUpdate() {
	spriteRenderDataComp_->uvTransform.scale.x = 0.5f;
	if (flagComp_->GetIsActive()) {
		spriteRenderDataComp_->uvTransform.translate.x = 0.5f;
	}
	else {
		spriteRenderDataComp_->uvTransform.translate.x = 0.0f;
	}
}

void SpriteUVChangeComp::EnableFlag()
{
	flagComp_->SetIsActive(true);
}

void SpriteUVChangeComp::UnenableFlag()
{
	flagComp_->SetIsActive(false);
}
