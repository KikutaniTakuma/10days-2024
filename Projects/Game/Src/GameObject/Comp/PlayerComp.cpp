#include "PlayerComp.h"
#include "TransformComp.h"
#include "SpriteRenderComp.h"
#include "InputMoveComp.h"
#include "FallComp.h"
#include "ObbPushComp.h"
#include "FlagComp.h"
#include "Direction2DComp.h"
#include "CsvDataComp.h"
#include "EatCloudComp.h"
#include "RemoveCloudComp.h"
#include "CountComp.h"
#include "Mass2DComp.h"
#include "Game/TileName/TileName.h"
#include "Input/Input.h"
#include "../Manager/CloudManager.h"
#include "JumpComp.h"
#include "Aabb2DComp.h"
#include "InvisibleComp.h"
#include "SpriteAnimatorComp.h"
#include "SpriteRenderDataComp.h"
#include "TextureHandlesComp.h"
#include "KeyComp.h"
#include "EaseingComp.h"
#include "SceneChangeComp.h"
#include "../Manager/ObjectManager.h"
#include "EventComp.h"


#include "AudioManager/AudioManager.h"

void PlayerComp::Init() {

	transform_ = object_.AddComp<TransformComp>();
	sprite_ = object_.AddComp<SpriteRenderComp>();
	spriteRenderData_ = object_.AddComp<SpriteRenderDataComp>();
	move_ = object_.AddComp<InputMoveComp>();
	fall_ = object_.AddComp<FallComp>();
	collision_ = object_.AddComp<ObbPushComp>();
	isDead_ = object_.AddComp<FlagComp>();	
	direction_ = object_.AddComp<Direction2DComp>();
	csvData_ = object_.AddComp<CsvDataComp>();
	eatCloud_ = object_.AddComp<EatCloudComp>();
	removeCloud_ = object_.AddComp<RemoveCloudComp>();
	count_ = object_.AddComp<CountComp>();
	mass_ = object_.AddComp<Mass2DComp>();
	jump_ = object_.AddComp<JumpComp>();
	aabbCollision_ = object_.AddComp<Aabb2DComp>();
	prePositions_ = std::make_unique<std::array<Vector3, 4>>();
	invisible_ = object_.AddComp<InvisibleComp>();
	animation_ = object_.AddComp<SpriteAnimatorComp>();
	handles_ = object_.AddComp<TextureHandlesComp>();
	easing_ = object_.AddComp<EaseingComp>();
	sceneChangeComp_ = object_.AddComp<SceneChangeComp>();

}

void PlayerComp::FirstUpdate() {

	/*transform_->scale = { 48.0f,48.0f,48.0f };
	collision_->GetObbComp().scale = { 0.5f,0.5f,0.5f };
	aabbCollision_->scale_ = { 0.5f,0.5f,0.5f };*/

}

void PlayerComp::Move() {

	Lamb::SafePtr gamepad = Input::GetInstance()->GetGamepad();
	Lamb::SafePtr key = Input::GetInstance()->GetKey();
	Lamb::SafePtr mouse = Input::GetInstance()->GetMouse();

	if (not isGoal_ and not sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent) {

		//シーンリセット
		if ((gamepad->Pushed(Gamepad::Button::X) or key->Pushed(DIK_R)) and
			not sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent) {
			sceneChangeComp_->SetNextScene(ObjectManager::GetInstance()->GetCurrentSceneFilePath());
			sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent = true;

			if (not stageResetAudio_->IsStart()) {
				stageResetAudio_->Start(0.3f, false);
			}
		}
		else if ((gamepad->Pushed(Gamepad::Button::START) or key->Pushed(DIK_ESCAPE)) and
			not sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent) {
			sceneChangeComp_->SetNextScene("./SceneData/stageSelect.json");
			sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent = true;

			if(not stageSelectAudio_->IsStart()) {
				stageSelectAudio_->Start(0.3f, false);
			}
		}


		if (not isStartEatAnimation_ and not isStartRemoveAnimation_) {

			velocity_.x = move_->GetMoveVector().x;

			if (gamepad->Pushed(Gamepad::Button::A) and onGround_) {

				jump_->Stop();
				jump_->Start();
				onGround_ = false;

			}

			if (key->Pushed(DIK_SPACE) and onGround_) {

				jump_->Stop();
				jump_->Start();
				onGround_ = false;

			}

			if (fabsf(move_->GetDirection().Length()) > 0.01f) {
				direction_->direction_ = { move_->GetMoveVector().x, move_->GetMoveVector().y };
			}

			if (fabsf(velocity_.x) > 0.01f) {

				if (spriteRenderData_->texHandle != handles_->textureHandles_[1 + invisibleValue_]) {
					spriteRenderData_->texHandle = handles_->textureHandles_[1 + invisibleValue_];
					animation_->Reset();
				}


			}
			else {
				if (spriteRenderData_->texHandle != handles_->textureHandles_[0 + invisibleValue_]) {
					spriteRenderData_->texHandle = handles_->textureHandles_[0 + invisibleValue_];
					animation_->Reset();
				}
			}

			if (not onGround_ and not fall_->GetIsFall()) {
				fall_->Start();
			}

			velocity_.y += jump_->GetJumpVelocity();

			if (not onGround_) {
				velocity_.y += +fall_->GetDeltaFall();
			}

			for (size_t i = 0; i < static_cast<size_t>(Aabb2DComp::Point::kNum); i++) {
				prePositions_->at(i) = aabbCollision_->GetPosition(static_cast<Aabb2DComp::Point>(i));
			}

			tmpPosition_ = transform_->translate;

			tmpPosition_ += velocity_;

			transform_->translate = tmpPosition_;
			transform_->UpdateMatrix();

			aabbCollision_->UpdatePosAndOrient();

			CheckCollision();

			transform_->translate = tmpPosition_;

			if (onGround_) {
				fall_->Stop();
				velocity_.y = 0.0f;
			}

			//雲が10未満でRボタンかトリガーを押したら食事開始。吐き出す動作とは重複しない
			if (not eatCloud_->isEat_ and count_->GetCount() < 10 and onGround_ and
				not gamepad->Pushed(Gamepad::Button::LEFT_SHOULDER) and not gamepad->Pushed(Gamepad::Trigger::LEFT) and
				(gamepad->Pushed(Gamepad::Button::RIGHT_SHOULDER) or gamepad->Pushed(Gamepad::Trigger::RIGHT))) {

				eatCloud_->isEat_ = true;
				animation_->Reset();
				animation_->SetDuration(0.0416f);
				spriteRenderData_->texHandle = handles_->textureHandles_[2 + invisibleValue_];
				isStartEatAnimation_ = true;

			}

			//雲を持っていてLボタンかトリガーを押したら吐き出し開始。食べる動作とは重複しない
			if (not removeCloud_->isRemove_ and count_->GetCount() > 0 and onGround_
				and (gamepad->Pushed(Gamepad::Button::LEFT_SHOULDER) or gamepad->Pushed(Gamepad::Trigger::LEFT)) and
				not gamepad->Pushed(Gamepad::Button::RIGHT_SHOULDER) and not gamepad->Pushed(Gamepad::Trigger::RIGHT)) {

				removeCloud_->isRemove_ = true;
				animation_->Reset();
				animation_->SetDuration(0.0416f);
				spriteRenderData_->texHandle = handles_->textureHandles_[3 + invisibleValue_];
				isStartRemoveAnimation_ = true;

			}

			//雲が10未満でRボタンかトリガーを押したら食事開始。吐き出す動作とは重複しない
			if (not eatCloud_->isEat_ and count_->GetCount() < 10 and onGround_ and
				not key->Pushed(DIK_Q) and key->Pushed(DIK_E)) {

				eatCloud_->isEat_ = true;
				animation_->Reset();
				animation_->SetDuration(0.0416f);
				spriteRenderData_->texHandle = handles_->textureHandles_[2 + invisibleValue_];
				isStartEatAnimation_ = true;

			}

			//雲を持っていてLボタンかトリガーを押したら吐き出し開始。食べる動作とは重複しない
			if (not removeCloud_->isRemove_ and count_->GetCount() > 0 and onGround_
				and key->Pushed(DIK_Q) and not key->Pushed(DIK_E)) {

				removeCloud_->isRemove_ = true;
				animation_->Reset();
				animation_->SetDuration(0.0416f);
				spriteRenderData_->texHandle = handles_->textureHandles_[3 + invisibleValue_];
				isStartRemoveAnimation_ = true;

			}

		}
		else if (isStartEatAnimation_) {

			if (animation_->GetCurrentAnimationNumber() == 5) {
				animation_->Reset();
				animation_->SetDuration(0.1666f);
				isStartEatAnimation_ = false;
			}

			CheckCollision();

		}
		else if (isStartRemoveAnimation_) {

			if (animation_->GetCurrentAnimationNumber() == 5) {
				animation_->Reset();
				animation_->SetDuration(0.1666f);
				isStartRemoveAnimation_ = false;
			}

			CheckCollision();

		}

		//向きによってuvのスケールを変更
		animation_->DirectionInverse(direction_->IsLeft());

		if (direction_->IsLeft()) {
			spriteRenderData_->userOffsetTransform.translate.x = -0.06f;
		}
		else {
			spriteRenderData_->userOffsetTransform.translate.x = 0.06f;
		}

		spriteRenderData_->userOffsetTransform.translate.y = 0.1f;

		transform_->UpdateMatrix();

		if (keyTransform_) {

			keyTransform_->scale = { 24.0f,24.0f,24.0f };
			keyTransform_->translate = transform_->translate + Vector3{ 0.0f,32.0f,0.0f };

		}

		//デッドラインより下なら死亡扱いしてシーンチェンジ
		if (transform_->translate.y < deadLine_ and not sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent) {
			sceneChangeComp_->SetNextScene(ObjectManager::GetInstance()->GetCurrentSceneFilePath());
			sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent = true;
		}

		//ビームに当たっていたら死亡
		if (beamCollisionFlg_ and not sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent) {
			sceneChangeComp_->SetNextScene(ObjectManager::GetInstance()->GetCurrentSceneFilePath());
			sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent = true;
		}

	}
	//ゴール時の移動演出
	else if(isGoal_) {

		//鍵を持っていたらスケールを0にして消す
		if (keyTransform_) {
			keyTransform_->scale = { 0.0f,0.0f,0.0f };
		}

		if (not onGround_ and not fall_->GetIsFall()) {
			fall_->Start();
		}

		velocity_.y += jump_->GetJumpVelocity();

		if (not onGround_) {
			velocity_.y += +fall_->GetDeltaFall();
		}

		for (size_t i = 0; i < static_cast<size_t>(Aabb2DComp::Point::kNum); i++) {
			prePositions_->at(i) = aabbCollision_->GetPosition(static_cast<Aabb2DComp::Point>(i));
		}

		tmpPosition_ = transform_->translate;

		tmpPosition_ += velocity_;

		transform_->translate = tmpPosition_;
		transform_->UpdateMatrix();

		aabbCollision_->UpdatePosAndOrient();

		CheckCollision();

		transform_->translate = tmpPosition_;

		if (onGround_) {
			fall_->Stop();
			velocity_.y = 0.0f;
		}

		if (isGoal_ and not easing_->GetEaseing().GetIsActive() and not isFirstEasingStart_) {
			easing_->isLoop = false;
			easing_->spdT = 1.0f;
			easing_->type = Easeing::Type::kNone;
			easing_->GetEaseing().Start(easing_->isLoop, easing_->spdT, easing_->type);
			isFirstEasingStart_ = true;
		}

		if (easing_->GetEaseing().GetIsActive()) {
			transform_->translate.x = easing_->GetEaseing().Get(easingStartX_, easingEndX_);
			transform_->scale = easing_->GetEaseing().Get(easingScaleStart_, easingScaleEnd_);
		}
		else {
			transform_->translate.x = easingEndX_;
		}

		isEasing_ = easing_->GetEaseing().GetIsActive();

	}

}

void PlayerComp::Event() {

	if (onGround_) {
		fall_->Stop();
	}

	//透明なら画像の変更処理
	if (invisible_->GetIsInvisible()) {

		invisibleValue_ = 4;

		//鍵を持っていたら落とすようにする
		if (key_) {

			key_->SetIsObtained(false);
			keyTransform_->scale = { 32.0f,32.0f,32.0f };
			keyTransform_->translate = Vector3{ float(mass_->GetMassX()) * 32.0f, -float(mass_->GetMassY()) * 32.0f, 1.0f };
			csvData_->SetNumber(mass_->GetMassX(), mass_->GetMassY(), static_cast<int32_t>(TileName::kKey));
			RemoveKey();

		}

	}
	else {
		invisibleValue_ = 0;
	}

}

void PlayerComp::Update() {

}

void PlayerComp::LastUpdate() {

}

void PlayerComp::SetKey(KeyComp* keyComp)
{

	key_ = keyComp;
	if (key_.empty()) {
		return;
	}

	keyTransform_ = key_->getObject().GetComp<TransformComp>();

}

void PlayerComp::RemoveKey()
{

	if (keyTransform_) {
		keyTransform_ = nullptr;
	}

	if (key_) {
		key_ = nullptr;
	}

}

void PlayerComp::CheckCollision()
{

	onGround_ = false;

	//雲のマネージャーからプレイヤーと当たっているオブジェクトを取ってくる
	for (auto cloud = CloudManager::GetInstance()->GetClouds().begin(); cloud != CloudManager::GetInstance()->GetClouds().end(); cloud++) {

		(*cloud)->GetAabb2DComp().UpdatePosAndOrient();

		//当たっている場合
		if (aabbCollision_->IsCollision(&(*cloud)->GetAabb2DComp())) {

			//左上
			if ((*cloud)->GetAabb2DComp().IsCollisionPoint(aabbCollision_->GetPosition(Aabb2DComp::Point::kLeftUp))) {

				//プレイヤーが右側から侵入したなら右に戻す
				if (prePositions_->at(static_cast<size_t>(Aabb2DComp::Point::kLeftUp)).y > (*cloud)->GetAabb2DComp().GetPosition(Aabb2DComp::Point::kRightUnder).y + 1.0f) {
					
					tmpPosition_.x = (*cloud)->GetAabb2DComp().GetPosition(Aabb2DComp::Point::kRightUnder).x + kPlayerHalfSize_;

					transform_->translate = tmpPosition_;
					transform_->UpdateMatrix();

					aabbCollision_->UpdatePosAndOrient();

				}
				else {

					//下側から侵入しているなら下に戻す
					if (prePositions_->at(static_cast<size_t>(Aabb2DComp::Point::kLeftUp)).x < (*cloud)->GetAabb2DComp().GetPosition(Aabb2DComp::Point::kRightUnder).x - 1.0f) {
						
						tmpPosition_.y = (*cloud)->GetAabb2DComp().GetPosition(Aabb2DComp::Point::kRightUnder).y - kPlayerHalfSize_;

						transform_->translate = tmpPosition_;
						transform_->UpdateMatrix();

						aabbCollision_->UpdatePosAndOrient();

						//ジャンプ中だったらジャンプ止める
						if (velocity_.y > 0.0f) {
							jump_->Stop();
							fall_->Stop();
							velocity_.y = 0.0f;
							fall_->Start();
						}

					}

				}

			}
			//右上
			if ((*cloud)->GetAabb2DComp().IsCollisionPoint(aabbCollision_->GetPosition(Aabb2DComp::Point::kRightUp))) {

				//プレイヤーが左側から侵入したなら左に戻す
				if (prePositions_->at(static_cast<size_t>(Aabb2DComp::Point::kRightUp)).y > (*cloud)->GetAabb2DComp().GetPosition(Aabb2DComp::Point::kLeftUnder).y + 1.0f) {
					
					tmpPosition_.x = (*cloud)->GetAabb2DComp().GetPosition(Aabb2DComp::Point::kLeftUnder).x - kPlayerHalfSize_;

					transform_->translate = tmpPosition_;
					transform_->UpdateMatrix();

					aabbCollision_->UpdatePosAndOrient();

				}
				else {

					//下側から侵入しているなら下に戻す
					if (prePositions_->at(static_cast<size_t>(Aabb2DComp::Point::kRightUp)).x > (*cloud)->GetAabb2DComp().GetPosition(Aabb2DComp::Point::kLeftUnder).x) {

						tmpPosition_.y = (*cloud)->GetAabb2DComp().GetPosition(Aabb2DComp::Point::kRightUnder).y - kPlayerHalfSize_;

						transform_->translate = tmpPosition_;
						transform_->UpdateMatrix();

						aabbCollision_->UpdatePosAndOrient();

						//ジャンプ中だったらジャンプ止める
						if (velocity_.y > 0.0f) {
							jump_->Stop();
							fall_->Stop();
							velocity_.y = 0.0f;
							fall_->Start();
						}

					}

				}

			}
			//左下
			if ((*cloud)->GetAabb2DComp().IsCollisionPoint(aabbCollision_->GetPosition(Aabb2DComp::Point::kLeftUnder))) {

				//プレイヤーが右側から侵入したなら右に戻す
				if (prePositions_->at(static_cast<size_t>(Aabb2DComp::Point::kLeftUnder)).y < (*cloud)->GetAabb2DComp().GetPosition(Aabb2DComp::Point::kRightUp).y) {
					
					tmpPosition_.x = (*cloud)->GetAabb2DComp().GetPosition(Aabb2DComp::Point::kRightUp).x + kPlayerHalfSize_;

					transform_->translate = tmpPosition_;
					transform_->UpdateMatrix();

					aabbCollision_->UpdatePosAndOrient();

				}
				else {

					//乗っている足場の一つ上がブロックでなければ乗れる
					if (csvData_->GetNumber((*cloud)->GetMassX(), (*cloud)->GetMassY() - 1) != static_cast<int32_t>(TileName::kCloud)) {

						tmpPosition_.y = (*cloud)->GetAabb2DComp().GetPosition(Aabb2DComp::Point::kRightUp).y + kPlayerHalfSize_;

						transform_->translate = tmpPosition_;
						transform_->UpdateMatrix();

						aabbCollision_->UpdatePosAndOrient();

						fall_->Stop();
						velocity_.y = 0.0f;
						onGround_ = true;

					}

				}

			}
			//右下
			if ((*cloud)->GetAabb2DComp().IsCollisionPoint(aabbCollision_->GetPosition(Aabb2DComp::Point::kRightUnder))) {

				//プレイヤーが左側から侵入したなら左に戻す
				if (prePositions_->at(static_cast<size_t>(Aabb2DComp::Point::kRightUnder)).y < (*cloud)->GetAabb2DComp().GetPosition(Aabb2DComp::Point::kLeftUp).y) {
					
					tmpPosition_.x = (*cloud)->GetAabb2DComp().GetPosition(Aabb2DComp::Point::kLeftUp).x - kPlayerHalfSize_;

					transform_->translate = tmpPosition_;
					transform_->UpdateMatrix();

					aabbCollision_->UpdatePosAndOrient();

				}
				else {

					//乗っている足場の一つ上がブロックでなければ乗れる
					if (csvData_->GetNumber((*cloud)->GetMassX(), (*cloud)->GetMassY() - 1) != static_cast<int32_t>(TileName::kCloud)) {

						tmpPosition_.y = (*cloud)->GetAabb2DComp().GetPosition(Aabb2DComp::Point::kLeftUp).y + kPlayerHalfSize_;

						transform_->translate = tmpPosition_;
						transform_->UpdateMatrix();

						aabbCollision_->UpdatePosAndOrient();

						fall_->Stop();
						velocity_.y = 0.0f;
						onGround_ = true;

					}

				}

			}

			(*cloud)->SetIsHitPlayer(true);

		}
		else {
			(*cloud)->SetIsHitPlayer(false);
		}

		//obb当たり判定(雑)
		{

			//if ((*cloud)->GetObbPushComp().GetObbComp().GetIsCollision()) {

			//	if ((*cloud)->GetMassY() > mass_->GetMassY()) {


			//		if ((*cloud)->GetMassX() > mass_->GetMassX()) {

			//			//壁がない場合
			//			if (csvData_->GetNumber(mass_->GetMassX() + 1, mass_->GetMassY()) != static_cast<int32_t>(TileName::kCloud)) {

			//				//既定の高さより上なら地面
			//				if (transform_->translate.y - 30.0f > -float(mass_->GetMassY() + 1) * 32.0f) {
			//					return true;
			//				}

			//			}

			//		}
			//		else if ((*cloud)->GetMassX() < mass_->GetMassX()) {

			//			//壁がない場合
			//			if (csvData_->GetNumber(mass_->GetMassX() - 1, mass_->GetMassY()) != static_cast<int32_t>(TileName::kCloud)) {

			//				//既定の高さより上なら地面
			//				if (transform_->translate.y - 30.0f > -float(mass_->GetMassY() + 1) * 32.0f) {
			//					return true;
			//				}

			//			}

			//		}
			//		else {
			//			return true;
			//		}

			//	}

			//}

		}

	}

}

void PlayerComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void PlayerComp::Load([[maybe_unused]] nlohmann::json& json) {

}

void PlayerComp::Load()
{
	AudioManager::GetInstance()->Load("./Resources/Sounds/SE_backScene.mp3");
	stageSelectAudio_ = AudioManager::GetInstance()->Get("./Resources/Sounds/SE_backScene.mp3");
	AudioManager::GetInstance()->Load("./Resources/Sounds/SE_outgame_decision.mp3");
	stageResetAudio_ = AudioManager::GetInstance()->Get("./Resources/Sounds/SE_outgame_decision.mp3");
}

void PlayerComp::SetIsBeamCollision(const Lamb::Flg& collisionFlg)
{
	beamCollisionFlg_ = collisionFlg;
}

const Lamb::Flg& PlayerComp::GetIsInvisible() const
{
	return invisible_->GetIsInvisible();
}
