#include "KeyComp.h"
#include "TransformComp.h"
#include "SpriteRenderComp.h"
#include "Mass2DComp.h"
#include "Aabb2DComp.h"
#include "PlayerComp.h"
#include "CsvDataComp.h"
#include "AudioManager/AudioManager.h"

void KeyComp::Init()
{
	transformComp_ = object_.AddComp<TransformComp>();
	spriteRenderComp_ = object_.AddComp<SpriteRenderComp>();
	mass_ = object_.AddComp<Mass2DComp>();
	aabbCollision_ = object_.AddComp<Aabb2DComp>();
}

void KeyComp::Load() {
	AudioManager::GetInstance()->Load("./Resources/Sounds/SE_ingame_getCoin.mp3");
	getKeyAudio_ = AudioManager::GetInstance()->Get("./Resources/Sounds/SE_ingame_getCoin.mp3");
}

void KeyComp::LastUpdate() {
	if (getKeyAudio_ and isObtained_.OnEnter()) {
		getKeyAudio_->Start(0.3f, false);
	}
}

void KeyComp::Finalize() {
	if (getKeyAudio_) {
		getKeyAudio_->Stop();
	}
}

void KeyComp::Event()
{

	if (aabbCollision_->IsCollision(playerAabbCollision_.get())) {

		//透明でない場合且つ取得されていない場合のみ取得
		if (not player_->GetIsInvisible() and not isObtained_) {

			//取得した時にマス目を消す
			player_->getObject().GetComp<CsvDataComp>()->SetNumber(mass_->GetMassX(), mass_->GetMassY(), 0);
			player_->SetKey(this);
			isObtained_ = true;

		}

	}

}

void KeyComp::SetPlayerComp(PlayerComp* playerComp)
{

	player_ = playerComp;
	if (player_.empty()) {
		return;
	}

	playerAabbCollision_ = player_->getObject().GetComp<Aabb2DComp>();

}

void KeyComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void KeyComp::Load([[maybe_unused]] nlohmann::json& json) {

}

