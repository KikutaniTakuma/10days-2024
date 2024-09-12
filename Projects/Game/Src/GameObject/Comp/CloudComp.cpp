#include "CloudComp.h"
#include "TransformComp.h"
#include "SpriteRenderComp.h"
#include "FlagComp.h"
#include "ObbPushComp.h"
#include "Mass2DComp.h"
#include "SpriteRenderDataComp.h"
#include "../Manager/CloudManager.h"
#include "Aabb2DComp.h"

void CloudComp::Init() {

	CloudManager::GetInstance()->Set(this);
	transformComp_ = object_.AddComp<TransformComp>();
	spriteRenderComp_ = object_.AddComp<SpriteRenderComp>();
	spriteRenderDataComp_ = object_.AddComp<SpriteRenderDataComp>();
	collision_ = object_.AddComp<ObbPushComp>();
	collision_->SetPushTag("class PlayerComp");
	flagComp_ = object_.AddComp<FlagComp>();
	flagComp_->SetIsActive(true);
	mass_ = object_.AddComp<Mass2DComp>();
	aabbCollision_ = object_.AddComp<Aabb2DComp>();
	//spriteRenderDataComp_->uvTransform.scale.x = 0.25f;

}

void CloudComp::Update() {

	if (isDead_) {
		transformComp_->scale = { 0.0f,0.0f,0.0f };
		transformComp_->translate = { -9999.0f,9999.0f,-9999.0f };
	}

	//雲が存在している状態だったら表示
	if (flagComp_->GetIsActive()) {
		transformComp_->scale = { kCloudSize_,kCloudSize_,kCloudSize_ };
		collision_->GetObbComp().scale = { kCloudSize_ + 0.5f,kCloudSize_ + 0.5f,kCloudSize_ + 0.5f };
		aabbCollision_->scale_ = { kCloudSize_,kCloudSize_,kCloudSize_ };
	}
	//食べられて存在しなくなった場合は非表示
	else {
		transformComp_->scale = { 0.0f,0.0f,0.0f };
		collision_->GetObbComp().scale = { 0.0f,0.0f,0.0f };
		aabbCollision_->scale_ = { 0.0f,0.0f,0.0f };
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

Aabb2DComp& CloudComp::GetAabb2DComp()
{
	return *aabbCollision_;
}

const Aabb2DComp& CloudComp::GetAabb2DComp() const
{
	return *aabbCollision_;
}

ObbPushComp& CloudComp::GetObbPushComp()
{
	return *collision_;
}

const ObbPushComp& CloudComp::GetObbPushComp() const
{
	
	return *collision_;

}
