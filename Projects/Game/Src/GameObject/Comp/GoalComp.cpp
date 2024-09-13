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
#include "AudioManager/AudioManager.h"

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

void GoalComp::Load() {
	AudioManager::GetInstance()->Load("./Resources/Sounds/SE_ingame_goal_open_close.mp3");
	openDoorAudio_ = AudioManager::GetInstance()->Get("./Resources/Sounds/SE_ingame_goal_open_close.mp3");
}

void GoalComp::Event()
{

	if (not isGoal_->GetIsActive()) {

		if (isOpen_) {
			spriteRenderDataComp_->texHandle = handles_->textureHandles_[0];
		}
		else {
			spriteRenderDataComp_->texHandle = handles_->textureHandles_[1];
		}

	}
	else {

	}

	if (player_.empty()) {
		return;
	}

	//プレイヤーのイージングが終了したらゴールフラグを立てる
	if (player_->GetIsGoal() and not isGoal_->GetIsActive() and not player_->GetIsEasing()) {
		isGoal_->SetIsActive(true);
	}

	//プレイヤーがゴールに触れたらフラグを立てる
	if (not player_->GetIsGoal() and playerAabbCollision_->IsCollision(aabbCollision_.get()) and not player_->GetIsInvisible()) {
		
		if (isOpen_) {
			player_->easingStartX_ = player_->getObject().GetComp<TransformComp>()->translate.x;
			player_->easingEndX_ = transformComp_->translate.x;
			player_->SetIsGoal(true);
		}
		else {
			
			if (player_->IsGetKey()) {
				player_->easingStartX_ = player_->getObject().GetComp<TransformComp>()->translate.x;
				player_->easingEndX_ = transformComp_->translate.x;
				player_->SetIsGoal(true);
			}

		}
		
	}

}

void GoalComp::Update()
{

	//ゴールした時
	if (isGoal_->GetIsActive().OnEnter()) {

		//開いていたら閉まる演出
		if (isOpen_) {
			spriteRenderDataComp_->texHandle = handles_->textureHandles_[3];
			animation_->Reset();
			animation_->SetAnimationNumber(8);
			animation_->SetDuration(0.125f);
			animation_->Start();
			animation_->SetLoopAnimation(false);
			//プレイヤーの座標を奥にする
			player_->getObject().GetComp<TransformComp>()->translate.z = 3.0f;
			isOpen_ = false;
			openDoorAudio_->Start(0.3f, false);
		}
		//閉じていたら開く演出から入る
		else {
			spriteRenderDataComp_->texHandle = handles_->textureHandles_[2];
			animation_->Reset();
			animation_->SetAnimationNumber(8);
			animation_->SetDuration(0.125f);
			animation_->Start();
			animation_->SetLoopAnimation(false);
			isOpen_ = true;

			// ここに音を挿入する
			openDoorAudio_->Start(0.3f, false);
		}

	}

	//ゴールしてアニメーションが終わって扉が開いている時
	if (isGoal_ and not animation_->GetIsActive() and isOpen_) {

		spriteRenderDataComp_->texHandle = handles_->textureHandles_[3];
		animation_->SetAnimationNumber(8);
		animation_->SetDuration(0.125f);
		animation_->Start();
		animation_->SetLoopAnimation(false);
		//プレイヤーの座標を奥にする
		player_->getObject().GetComp<TransformComp>()->translate.z = 3.0f;
		isOpen_ = false;

		// ここに音を挿入する
		openDoorAudio_->Start(0.3f, false);

	}

	//扉が閉じるコマに入ったらアニメーションを止め、扉を閉じたフラグを立てる
	if (player_->GetIsGoal() and not player_->GetIsEasing() and isGoal_ and
		animation_->GetIsActive() and not isOpen_ and animation_->GetCurrentAnimationNumber() == 7) {
		animation_->Pause();
		isCloseDoor_ = true;
	}

}

void GoalComp::Finalize() {
	if (openDoorAudio_) {
		openDoorAudio_->Stop();
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

