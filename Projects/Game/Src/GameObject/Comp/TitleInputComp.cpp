#include "TitleInputComp.h"
#include "Input/Input.h"
#include "SceneChangeComp.h"
#include "EventComp.h"

void TitleInputComp::Init()
{
	sceneChangeComp_ = object_.AddComp<SceneChangeComp>();
}

void TitleInputComp::Move()
{

	Lamb::SafePtr gamepad = Input::GetInstance()->GetGamepad();
	Lamb::SafePtr key = Input::GetInstance()->GetKey();
	Lamb::SafePtr mouse = Input::GetInstance()->GetMouse();

	if (not sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent) {

		//ボタンを押してセレクトシーンに移動
		if (gamepad->Pushed(Gamepad::Button::A)) {
			sceneChangeComp_->SetNextScene("./SceneData/stageSelect.json");
			sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent = true;
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
