#include "GoalComp.h"
#include "Aabb2DComp.h"
#include "SpriteRenderComp.h"
#include "TransformComp.h"
#include "Mass2DComp.h"
#include "PlayerComp.h"
#include "FlagComp.h"

void GoalComp::Init()
{
	transformComp_ = object_.AddComp<TransformComp>();
	aabbCollision_ = object_.AddComp<Aabb2DComp>();
	spriteRenderComp_ = object_.AddComp<SpriteRenderComp>();
	mass_ = object_.AddComp<Mass2DComp>();
	isGoal_ = object_.AddComp<FlagComp>();
}

void GoalComp::Event()
{

	if (player_.empty()) {
		return;
	}

	//プレイヤーがゴールに触れたらフラグを立てる
	if (playerAabbCollision_->IsCollision(aabbCollision_.get())) {
		isGoal_->SetIsActive(true);
	}

}

void GoalComp::SetPlayerComp(PlayerComp* playerComp)
{

	player_ = playerComp;
	if (player_.empty()) {
		return;
	}

	playerAabbCollision_ = player_->getObject().GetComp<Aabb2DComp>();

}

const Lamb::Flg& GoalComp::GetIsGoal() const
{
	return isGoal_->GetIsActive();
}

void GoalComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void GoalComp::Load([[maybe_unused]] nlohmann::json& json) {

}

