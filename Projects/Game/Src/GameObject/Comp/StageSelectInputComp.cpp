#include "StageSelectInputComp.h"
#include "Input/Input.h"
#include "SceneChangeComp.h"
#include "EventComp.h"

int32_t StageSelectInputComp::stageNumber_ = 1;

void StageSelectInputComp::Init()
{
	sceneChangeComp_ = object_.AddComp<SceneChangeComp>();
}

void StageSelectInputComp::Move()
{

	Lamb::SafePtr gamepad = Input::GetInstance()->GetGamepad();
	Lamb::SafePtr key = Input::GetInstance()->GetKey();
	Lamb::SafePtr mouse = Input::GetInstance()->GetMouse();

	if (not sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent) {

		if (gamepad->Pushed(Gamepad::Button::A)) {

			std::string stageStr = "./SceneData/stage";

			stageStr += std::to_string(stageNumber_);

			stageStr += ".json";

			sceneChangeComp_->SetNextScene(stageStr);
			sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent = true;

		}
		else if (gamepad->Pushed(Gamepad::Button::B)) {
			//ボタンを押してセレクトシーンに移動
			sceneChangeComp_->SetNextScene("./SceneData/title.json");
			sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent = true;
		}
		else if (gamepad->Pushed(Gamepad::Button::LEFT) or gamepad->GetStick(Gamepad::Stick::LEFT).x < 0.0f) {

			if (stageNumber_ > 1) {
				stageNumber_--;
			}

		}
		else if (gamepad->Pushed(Gamepad::Button::RIGHT) or gamepad->GetStick(Gamepad::Stick::LEFT).x > 0.0f) {

			if (stageNumber_ < kMaxStage_) {
				stageNumber_++;
			}

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
