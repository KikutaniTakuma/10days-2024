#include "CollectionComp.h"
#include "TransformComp.h"
#include "SpriteRenderComp.h"
#include "Mass2DComp.h"
#include "Aabb2DComp.h"
#include "PlayerComp.h"
#include "CsvDataComp.h"

void CollectionComp::Init()
{
	transformComp_ = object_.AddComp<TransformComp>();
	spriteRenderComp_ = object_.AddComp<SpriteRenderComp>();
	mass_ = object_.AddComp<Mass2DComp>();
	aabbCollision_ = object_.AddComp<Aabb2DComp>();
}

void CollectionComp::Event()
{

	//取得されていたらスケール0
	if (isObtained_) {
		transformComp_->scale = { 0.0f,0.0f,0.0f };
	}
	else {
		transformComp_->scale = { 32.0f,32.0f,32.0f };
	}

	if (aabbCollision_->IsCollision(playerAabbCollision_.get())) {

		//取得した時にマス目を消す
		player_->getObject().GetComp<CsvDataComp>()->SetNumber(mass_->GetMassX(), mass_->GetMassY(), 0);
		//取得フラグを立てる
		isObtained_ = true;
		//コインカウントプラス
		player_->AddCoin();

	}

}

void CollectionComp::SetPlayerComp(PlayerComp* playerComp)
{

	player_ = playerComp;
	if (player_.empty()) {
		return;
	}

	playerAabbCollision_ = player_->getObject().GetComp<Aabb2DComp>();

}

void CollectionComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void CollectionComp::Load([[maybe_unused]] nlohmann::json& json) {

}

