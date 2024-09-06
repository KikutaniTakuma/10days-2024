#include "CloudComp.h"
#include "TransformComp.h"
#include "SpriteRenderComp.h"
#include "FlagComp.h"
#include "ObbPushComp.h"

void CloudComp::Init() {

	transformComp_ = object_.AddComp<TransformComp>();
	spriteRenderComp_ = object_.AddComp<SpriteRenderComp>();
	collision_ = object_.AddComp<ObbPushComp>();
	collision_->SetPushTag("class PlayerComp");
	flagComp_ = object_.AddComp<FlagComp>();
	flagComp_->SetIsActive(true);

}

void CloudComp::Update() {

	//雲が存在している状態だったら表示
	if (flagComp_->GetIsActive()) {
		transformComp_->scale = { cloudSize_,cloudSize_,cloudSize_ };
	}
	//食べられて存在しなくなった場合は非表示
	else {
		transformComp_->scale = { 0.0f,0.0f,0.0f };
	}


}

void CloudComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void CloudComp::Load([[maybe_unused]] nlohmann::json& json) {

}
