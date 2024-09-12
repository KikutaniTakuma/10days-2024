#include "ResultInputComp.h"
#include "Input/Input.h"
#include "SceneChangeComp.h"
#include "EventComp.h"
#include "ResultInputComp.h"
#include "GoalComp.h"

void ResultInputComp::Init()
{
	sceneChangeComp_ = object_.AddComp<SceneChangeComp>();
}

void ResultInputComp::Move()
{

	Lamb::SafePtr gamepad = Input::GetInstance()->GetGamepad();
	Lamb::SafePtr key = Input::GetInstance()->GetKey();
	Lamb::SafePtr mouse = Input::GetInstance()->GetMouse();

	if (goalComp_) {

		if (goalComp_->GetIsGoal()) {

			

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
