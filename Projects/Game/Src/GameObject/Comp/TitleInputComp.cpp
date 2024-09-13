#include "TitleInputComp.h"
#include "Input/Input.h"
#include "SceneChangeComp.h"
#include "EventComp.h"
#include "AudioManager/AudioManager.h"

void TitleInputComp::Init()
{
	sceneChangeComp_ = object_.AddComp<SceneChangeComp>();
	AudioManager::GetInstance()->Load("./Resources/Sounds/SE_outgame_decision.mp3");
	pushButtonAudio_ = AudioManager::GetInstance()->Get("./Resources/Sounds/SE_outgame_decision.mp3");
}

void TitleInputComp::Move()
{

	Lamb::SafePtr gamepad = Input::GetInstance()->GetGamepad();
	Lamb::SafePtr key = Input::GetInstance()->GetKey();
	Lamb::SafePtr mouse = Input::GetInstance()->GetMouse();

	if (not sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent) {

		//ボタンを押してセレクトシーンに移動
		if (gamepad->Pushed(Gamepad::Button::A) or key->Pushed(DIK_SPACE)) {
			sceneChangeComp_->SetNextScene("./SceneData/stageSelect.json");
			sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent = true;
			pushButtonAudio_->Start(0.3f, false);
		}

	}

}

void TitleInputComp::Debug([[maybe_unused]] const std::string& guiName) {

}

void TitleInputComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void TitleInputComp::Load([[maybe_unused]] nlohmann::json& json)
{
}
