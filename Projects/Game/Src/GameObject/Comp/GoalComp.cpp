#include "GoalComp.h"
#include "Aabb2DComp.h"
#include "SpriteRenderComp.h"
#include "TransformComp.h"
#include "Mass2DComp.h"
#include "PlayerComp.h"
#include "FlagComp.h"
#include "SpriteAnimatorComp.h"
#include "SpriteRenderDataComp.h"
#include "TextureHandlesComp.h"

void GoalComp::Init()
{
	transformComp_ = object_.AddComp<TransformComp>();
	aabbCollision_ = object_.AddComp<Aabb2DComp>();
	spriteRenderComp_ = object_.AddComp<SpriteRenderComp>();
	spriteRenderDataComp_ = object_.AddComp<SpriteRenderDataComp>();
	mass_ = object_.AddComp<Mass2DComp>();
	isGoal_ = object_.AddComp<FlagComp>();
	animation_ = object_.AddComp<SpriteAnimatorComp>();
	handles_ = object_.AddComp<TextureHandlesComp>();
}

void GoalComp::Event()
{

	if (isOpen_) {
		spriteRenderDataComp_->texHandle = handles_->textureHandles_[0];
	}
	else {
		spriteRenderDataComp_->texHandle = handles_->textureHandles_[1];
	}

	if (player_.empty()) {
		return;
	}

	//プレイヤーがゴールに触れたらフラグを立てる
	if (not isGoal_->GetIsActive() and playerAabbCollision_->IsCollision(aabbCollision_.get())) {
		
		if (isOpen_) {
			isGoal_->SetIsActive(true);
		}
		else {
			
			if (player_->IsGetKey()) {
				isGoal_->SetIsActive(true);
			}

		}
		
	}

}

void GoalComp::Update()
{

	if (isGoal_->GetIsActive().OnEnter()) {

		

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

