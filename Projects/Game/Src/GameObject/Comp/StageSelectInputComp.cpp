#include "StageSelectInputComp.h"
#include "Input/Input.h"
#include "SceneChangeComp.h"
#include "EventComp.h"
#include "AudioManager/AudioManager.h"

int32_t StageSelectInputComp::stageNumber_ = 1;

void StageSelectInputComp::Init()
{
	sceneChangeComp_ = object_.AddComp<SceneChangeComp>();
	AudioManager::GetInstance()->Load("./Resources/Sounds/SE_stageSelect_move.mp3");
	arrowAudio_ = AudioManager::GetInstance()->Get("./Resources/Sounds/SE_stageSelect_move.mp3");
	AudioManager::GetInstance()->Load("./Resources/Sounds/SE_outgame_decision.mp3");
	pushButtonAudio_ = AudioManager::GetInstance()->Get("./Resources/Sounds/SE_outgame_decision.mp3");
	AudioManager::GetInstance()->Load("./Resources/Sounds/SE_backScene.mp3");
	backSceneAudio_ = AudioManager::GetInstance()->Get("./Resources/Sounds/SE_backScene.mp3");
}

void StageSelectInputComp::Move()
{

	Lamb::SafePtr gamepad = Input::GetInstance()->GetGamepad();
	Lamb::SafePtr key = Input::GetInstance()->GetKey();
	Lamb::SafePtr mouse = Input::GetInstance()->GetMouse();

	if (not sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent) {

		if (gamepad->Pushed(Gamepad::Button::A) or key->Pushed(DIK_SPACE)) {

			std::string stageStr = "./SceneData/stage";

			stageStr += std::to_string(stageNumber_);

			stageStr += ".json";

			sceneChangeComp_->SetNextScene(stageStr);
			sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent = true;
			pushButtonAudio_->Start(0.3f, false);

		}
		else if (gamepad->Pushed(Gamepad::Button::START) or key->Pushed(DIK_ESCAPE)) {
			//ボタンを押してセレクトシーンに移動
			sceneChangeComp_->SetNextScene("./SceneData/title.json");
			sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent = true;
			backSceneAudio_->Start(0.3f, false);
		}
		else if ((gamepad->Pushed(Gamepad::Button::LEFT) or
			(gamepad->GetStick(Gamepad::Stick::LEFT).x < 0.0f) or
			key->Pushed(DIK_A) or key->Pushed(DIK_LEFT))) {

			if (stageNumber_ > 1 and not isStickUsed_) {
				stageNumber_--;
				arrowAudio_->Start(0.3f, false);
			}

			isStickUsed_ = true;

		}
		else if ((gamepad->Pushed(Gamepad::Button::RIGHT) or
			(gamepad->GetStick(Gamepad::Stick::LEFT).x > 0.0f) or
			key->Pushed(DIK_D) or key->Pushed(DIK_RIGHT))) {

			if (stageNumber_ < kMaxStage_ and not isStickUsed_) {
				stageNumber_++;
				arrowAudio_->Start(0.3f, false);
			}

			isStickUsed_ = true;

		}
		else {
			isStickUsed_ = false;
		}

	}

}

void StageSelectInputComp::Debug([[maybe_unused]] const std::string& guiName) {

}

void StageSelectInputComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void StageSelectInputComp::Load([[maybe_unused]] nlohmann::json& json)
{
}
