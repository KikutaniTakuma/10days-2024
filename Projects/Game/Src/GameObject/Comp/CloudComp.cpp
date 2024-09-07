#include "CloudComp.h"
#include "TransformComp.h"
#include "SpriteRenderComp.h"
#include "FlagComp.h"
#include "ObbPushComp.h"
#include "Mass2DComp.h"
#include "../Manager/CloudManager.h"

void CloudComp::Init() {

	CloudManager::GetInstance()->Set(this);
	transformComp_ = object_.AddComp<TransformComp>();
	spriteRenderComp_ = object_.AddComp<SpriteRenderComp>();
	collision_ = object_.AddComp<ObbPushComp>();
	collision_->SetPushTag("class PlayerComp");
	flagComp_ = object_.AddComp<FlagComp>();
	flagComp_->SetIsActive(true);
	mass_ = object_.AddComp<Mass2DComp>();

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

void CloudComp::Finalize()
{
	CloudManager::GetInstance()->Erase(this);
}

const Lamb::Flg& CloudComp::GetIsActive() const
{
	return flagComp_->GetIsActive();
}

void CloudComp::SetIsActive(bool flag)
{
	flagComp_->SetIsActive(flag);
}

void CloudComp::SetPosition(const Vector3& position)
{
	transformComp_->translate = position;
}

int32_t CloudComp::GetMassX() const
{
	return mass_->GetMassX();
}

int32_t CloudComp::GetMassY() const
{
	return mass_->GetMassY();
}

void CloudComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void CloudComp::Load([[maybe_unused]] nlohmann::json& json) {

}
