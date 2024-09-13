#include "ResultInputComp.h"
#include "Input/Input.h"
#include "SceneChangeComp.h"
#include "EventComp.h"
#include "ResultInputComp.h"
#include "GoalComp.h"
#include "StageSelectInputComp.h"
#include "SpriteRenderDataComp.h"
#include "SpriteRenderComp.h"
#include "TransformComp.h"
#include "EaseingComp.h"

void ResultInputComp::Init()
{
	sceneChangeComp_ = object_.AddComp<SceneChangeComp>();
	spriteRenderComp_ = object_.AddComp<SpriteRenderComp>();
	spriteRenderDataComp_ = object_.AddComp<SpriteRenderDataComp>();
	transform_ = object_.AddComp<TransformComp>();
	easing_ = object_.AddComp<EaseingComp>();
}

void ResultInputComp::Move()
{

	Lamb::SafePtr gamepad = Input::GetInstance()->GetGamepad();
	Lamb::SafePtr key = Input::GetInstance()->GetKey();
	Lamb::SafePtr mouse = Input::GetInstance()->GetMouse();

	if (goalComp_) {

		if (goalComp_->GetIsCloseDoor()) {

			if (not sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent) {

				//10ステージ目では反応させない
				if (gamepad->Pushed(Gamepad::Button::A) or key->Pushed(DIK_SPACE) and 
					StageSelectInputComp::stageNumber_ < StageSelectInputComp::kMaxStage_) {

					//次のステージに移動
					StageSelectInputComp::stageNumber_++;

					std::string stageStr = "./SceneData/stage";

					stageStr += std::to_string(StageSelectInputComp::stageNumber_);

					stageStr += ".json";

					sceneChangeComp_->SetNextScene(stageStr);
					sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent = true;

				}
				else if (gamepad->Pushed(Gamepad::Button::B) or key->Pushed(DIK_ESCAPE)) {
					//ボタンを押してセレクトシーンに移動
					sceneChangeComp_->SetNextScene("./SceneData/stageSelect.json");
					sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent = true;
				}
				else if (gamepad->Pushed(Gamepad::Button::X) or key->Pushed(DIK_R)) {
					//ボタンを押してセレクトシーンに移動
					std::string stageStr = "./SceneData/stage";

					stageStr += std::to_string(StageSelectInputComp::stageNumber_);

					stageStr += ".json";

					sceneChangeComp_->SetNextScene(stageStr);
					sceneChangeComp_->getObject().GetComp<EventComp>()->isEvent = true;
				}

			}

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
