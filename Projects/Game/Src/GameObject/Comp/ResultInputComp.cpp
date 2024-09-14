#include "ResultInputComp.h"
#include "Input/Input.h"
#include "SceneChangeComp.h"
#include "EventComp.h"
#include "ResultInputComp.h"
#include "GoalComp.h"
#include "StageSelectInputComp.h"
#include "SpriteRenderDataComp.h"
#include "UISpriteRenderDataComp.h"
#include "SpriteRenderComp.h"
#include "TransformComp.h"
#include "EaseingComp.h"
#include "UIDrawComp.h"
#include "UITransformComp.h"
#include "EaseingComp.h"
#include "StarComp.h"
#include "ChildrenObjectComp.h"
#include "PlayerComp.h"
#include "UINumSpriteComp.h"

#include "AudioManager/AudioManager.h"

void ResultInputComp::Init()
{
	sceneChangeComp_ = object_.AddComp<SceneChangeComp>();
	spriteRenderDataComp_ = object_.AddComp<UISpriteRenderDataComp>();
	easing_ = object_.AddComp<EaseingComp>();
	UIDraw_ = object_.AddComp<UIDrawComp>();
	UITransform_ = object_.AddComp<UITransformComp>();
	childrenComp_ = object_.AddComp<ChildrenObjectComp>();
}

void ResultInputComp::Load() {
	
	AudioManager::GetInstance()->Load("./Resources/Sounds/SE_backScene.mp3");
	backAudio_ = AudioManager::GetInstance()->Get("./Resources/Sounds/SE_backScene.mp3");
	AudioManager::GetInstance()->Load("./Resources/Sounds/SE_outgame_decision.mp3");
	decideAudio_ = AudioManager::GetInstance()->Get("./Resources/Sounds/SE_outgame_decision.mp3");

	for (int32_t i = 0; i < 3; i++) {

		Lamb::SafePtr<Object> newObject = Lamb::MakeSafePtr<Object>();
		stars_.push_back(newObject->AddComp<StarComp>());
		auto starTransform = stars_.back()->getObject().GetComp<UITransformComp>();
		starTransform->translate = { 96.0f * float(i - 1), -50.0f, -2.0f };
		auto starRenderData = stars_.back()->getObject().GetComp<UISpriteRenderDataComp>();
		starRenderData->fileName = "./Resources/Textures/outGame/result_star_outline.png";
		starRenderData->type = BlendType::kNormal;
		starRenderData->Load();
		starRenderData->uvTransform.rotate = { 0.0f,0.0f,0.0f, 1.0f };
		childrenComp_->AddObject(newObject);
		starTransform->SetParent(nullptr);

	}

	Lamb::SafePtr<Object> newObject = Lamb::MakeSafePtr<Object>();
	buttonUIs_.push_back(newObject->AddComp<UIDrawComp>());
	auto transform = buttonUIs_.back()->getObject().GetComp<UITransformComp>();
	transform->translate = {-200.0f, -300.0f, -2.0f };
	auto renderData = buttonUIs_.back()->getObject().GetComp<UISpriteRenderDataComp>();
	renderData->fileName = "./Resources/Textures/UI/ingame_UI_reset.png";
	renderData->type = BlendType::kNormal;
	renderData->Load();
	renderData->uvTransform.rotate = { 0.0f,0.0f,0.0f, 1.0f };
	childrenComp_->AddObject(newObject);
	transform->SetParent(nullptr);

	newObject = Lamb::MakeSafePtr<Object>();
	buttonUIs_.push_back(newObject->AddComp<UIDrawComp>());
	transform = buttonUIs_.back()->getObject().GetComp<UITransformComp>();
	transform->translate = { 0.0f, -300.0f, -2.0f };
	renderData = buttonUIs_.back()->getObject().GetComp<UISpriteRenderDataComp>();
	renderData->fileName = "./Resources/Textures/UI/result_UI_B.png";
	renderData->type = BlendType::kNormal;
	renderData->Load();
	renderData->uvTransform.rotate = { 0.0f,0.0f,0.0f, 1.0f };
	childrenComp_->AddObject(newObject);
	transform->SetParent(nullptr);

	newObject = Lamb::MakeSafePtr<Object>();
	buttonUIs_.push_back(newObject->AddComp<UIDrawComp>());
	transform = buttonUIs_.back()->getObject().GetComp<UITransformComp>();
	transform->translate = { 200.0f, -300.0f, -2.0f };
	renderData = buttonUIs_.back()->getObject().GetComp<UISpriteRenderDataComp>();
	renderData->fileName = "./Resources/Textures/UI/result_UI_A.png";
	renderData->type = BlendType::kNormal;
	renderData->Load();
	renderData->uvTransform.rotate = { 0.0f,0.0f,0.0f, 1.0f };
	childrenComp_->AddObject(newObject);
	transform->SetParent(nullptr);

	for (int32_t i = 0; i < 2; i++) {

		Lamb::SafePtr<Object> newNumObject = Lamb::MakeSafePtr<Object>();
		nums_.push_back(newNumObject->AddComp<UINumSpriteComp>());
		auto numTransform = nums_.back()->getObject().GetComp<UITransformComp>();
		numTransform->translate = { 48.0f - 96.0f * float(i), 150.0f, -2.0f};
		auto numRenderData = nums_.back()->getObject().GetComp<UISpriteRenderDataComp>();
		numRenderData->fileName = "./Resources/Textures/outGame/num_white.png";
		numRenderData->type = BlendType::kNormal;
		numRenderData->uvTransform.scale.x = 0.1f;
		numRenderData->Load();
		numRenderData->uvTransform.rotate = { 0.0f,0.0f,0.0f, 1.0f };
		childrenComp_->AddObject(newNumObject);
		numTransform->SetParent(nullptr);

		if (i == 1) {
			nums_[i]->divide_ = 10;
		}

	}

}

void ResultInputComp::FirstUpdate()
{

	for (int32_t i = 0; i < 3; i++) {

		if (stars_[i]->getObject().GetComp<UITransformComp>()->HaveParent()) {
			stars_[i]->getObject().GetComp<UITransformComp>()->SetParent(nullptr);
		}

		if (buttonUIs_[i]->getObject().GetComp<UITransformComp>()->HaveParent()) {
			buttonUIs_[i]->getObject().GetComp<UITransformComp>()->SetParent(nullptr);
		}

	}

	for (int32_t i = 0; i < 2; i++) {

		if (nums_[i]->getObject().GetComp<UITransformComp>()->HaveParent()) {
			nums_[i]->getObject().GetComp<UITransformComp>()->SetParent(nullptr);
		}

	}

}

void ResultInputComp::Move()
{

	Lamb::SafePtr gamepad = Input::GetInstance()->GetGamepad();
	Lamb::SafePtr key = Input::GetInstance()->GetKey();
	Lamb::SafePtr mouse = Input::GetInstance()->GetMouse();

	if (goalComp_) {

		if (goalComp_->GetIsCloseDoor()) {

			if (not isEasingStart_) {

				easing_->isLoop = false;
				easing_->spdT = 1.0f;
				easing_->type = Easeing::Type::kInSine;
				easing_->GetEaseing().Start(easing_->isLoop, easing_->spdT, easing_->type);
				isEasingStart_ = true;

			}

			if (not sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent and stars_[2]->isEasingEnd_) {

				//10ステージ目では反応させない
				if ((gamepad->Pushed(Gamepad::Button::A) or key->Pushed(DIK_SPACE)) and 
					StageSelectInputComp::stageNumber_ < StageSelectInputComp::kMaxStage_) {

					//次のステージに移動
					StageSelectInputComp::stageNumber_++;

					std::string stageStr = "./SceneData/stage";

					stageStr += std::to_string(StageSelectInputComp::stageNumber_);

					stageStr += ".json";

					sceneChangeComp_->SetNextScene(stageStr);
					sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent = true;
					decideAudio_->Start(0.3f, false);

					//数字を更新させない
					for (size_t i = 0; i < 2; i++) {
						nums_[i]->isUpdate_ = false;
					}

				}
				else if (gamepad->Pushed(Gamepad::Button::B) or key->Pushed(DIK_ESCAPE)) {
					//ボタンを押してセレクトシーンに移動
					sceneChangeComp_->SetNextScene("./SceneData/stageSelect.json");
					sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent = true;
					backAudio_->Start(0.3f, false);
				}
				else if (gamepad->Pushed(Gamepad::Button::X) or key->Pushed(DIK_R)) {
					//ボタンを押してセレクトシーンに移動
					std::string stageStr = "./SceneData/stage";

					stageStr += std::to_string(StageSelectInputComp::stageNumber_);

					stageStr += ".json";

					sceneChangeComp_->SetNextScene(stageStr);
					sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent = true;
					decideAudio_->Start(0.3f, false);

				}

			}

		}

	}

	if (isEasingStart_) {
		UITransform_->scale = { 480.0f,480.0f,1.0f };

		for (int32_t i = 0; i < 2; i++) {
			nums_[i]->getObject().GetComp<UITransformComp>()->scale = { 48.0f,48.0f,48.0f };
		}

	}
	else {
		UITransform_->scale = { 0.0f,0.0f,0.0f };

		for (int32_t i = 0; i < 2; i++) {
			nums_[i]->getObject().GetComp<UITransformComp>()->scale = { 0.0f,0.0f,0.0f };
		}

	}

	if (easing_->GetEaseing().GetIsActive()) {
		UITransform_->translate = easing_->GetEaseing().Get(easingPositionStart_, easingPositionEnd_);

		for (int32_t i = 0; i < 2; i++) {
			nums_[i]->getObject().GetComp<UITransformComp>()->translate = 
				easing_->GetEaseing().Get(easingPositionStart_ + Vector3{ 32.0f - 64.0f * float(i), 150.0f, -2.0f },
					easingPositionEnd_ + Vector3{ 32.0f - 64.0f * float(i), 150.0f, -2.0f });
		}

	}
	else if (isEasingStart_) {
		
		UITransform_->translate = easingPositionEnd_;

		for (int32_t i = 0; i < 2; i++) {
			nums_[i]->getObject().GetComp<UITransformComp>()->translate = easingPositionEnd_ + Vector3{ 32.0f - 64.0f * float(i), 150.0f, -2.0f };
		}

	}

	for (size_t i = 0; i < 3; i++) {

		//イージングが完了しているなら
		if (not easing_->GetEaseing().GetIsActive() and isEasingStart_ and not stars_[2]->isEasingEnd_) {

			if (player_) {

				if (player_->GetCoinCount() > i) {
					stars_[i]->getObject().GetComp<UISpriteRenderDataComp>()->fileName = "./Resources/Textures/outGame/result_star.png";
					stars_[i]->getObject().GetComp<UISpriteRenderDataComp>()->Load();
				}
				else {
					stars_[i]->getObject().GetComp<UISpriteRenderDataComp>()->fileName = "./Resources/Textures/outGame/result_star_outline.png";
					stars_[i]->getObject().GetComp<UISpriteRenderDataComp>()->Load();
				}

			}

			if (i == 0) {

				if (not stars_[i]->isEasingStart_) {
					stars_[i]->Start();
				}

			}
			else {

				if (stars_[i - 1]->isEasingEnd_ and not stars_[i]->isEasingStart_) {
					stars_[i]->Start();
				}

			}

		}

	}

	if (stars_[2]->isEasingEnd_) {

		for (int32_t i = 0; i < 3; i++) {

			buttonUIs_[i]->getObject().GetComp<UITransformComp>()->scale = { 128.0f,128.0f,128.0f };

			if (i == 2 and StageSelectInputComp::stageNumber_ == 10) {
				buttonUIs_[i]->getObject().GetComp<UITransformComp>()->scale = { 0.0f,0.0f,0.0f };
			}

		}

	}
	else {

		for (int32_t i = 0; i < 3; i++) {

			buttonUIs_[i]->getObject().GetComp<UITransformComp>()->scale = { 0.0f,0.0f,0.0f };

		}

	}

}

void ResultInputComp::Debug([[maybe_unused]] const std::string& guiName) {

}

void ResultInputComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void ResultInputComp::Load([[maybe_unused]] nlohmann::json& json)
{
}

void ResultInputComp::SetGoal(GoalComp* goalComp)
{
	goalComp_ = goalComp;
}

void ResultInputComp::SetPlayer(PlayerComp* player)
{
	player_ = player;
}
