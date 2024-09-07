#include "RemoveCloudComp.h"
#include "TransformComp.h"
#include "Direction2DComp.h"
#include "CsvDataComp.h"
#include "Mass2DComp.h"
#include "CountComp.h"
#include "Game/TileName/TileName.h"
#include "Input/Input.h"

void RemoveCloudComp::Init()
{
	transform_ = object_.AddComp<TransformComp>();
	direction_ = object_.AddComp<Direction2DComp>();
	csvData_ = object_.AddComp<CsvDataComp>();
	mass_ = object_.AddComp<Mass2DComp>();
	count_ = object_.AddComp<CountComp>();
}

void RemoveCloudComp::FirstUpdate()
{

	Lamb::SafePtr gamepad = Input::GetInstance()->GetGamepad();
	Lamb::SafePtr key = Input::GetInstance()->GetKey();
	Lamb::SafePtr mouse = Input::GetInstance()->GetMouse();

	//雲を持っていてLボタンを押したら吐き出し開始。食べる動作とは重複しない
	if (not isRemove_ and count_->GetCount() > 0 and gamepad->Pushed(Gamepad::Button::LEFT_SHOULDER) and
		not gamepad->Pushed(Gamepad::Button::RIGHT_SHOULDER)) {

		isRemove_ = true;

	}

}

void RemoveCloudComp::Event()
{

	//吐き出しフラグが立っていたら
	if (isRemove_) {

		if (direction_->IsLeft()) {

			//隣のマスが空いていたら雲を吐き出す
			if (csvData_->GetNumber(mass_->GetMassX() - 1, mass_->GetMassY()) == static_cast<int32_t>(TileName::kNone)) {

				Vector3 newPosition = { float(mass_->GetMassX() - 1) * 32.0f, -float(mass_->GetMassY()) * 32.0f, 1.0f };

				CloudManager::GetInstance()->GetDeadCloud()->SetPosition(newPosition);

				CloudManager::GetInstance()->GetDeadCloud()->SetIsActive(true);

				csvData_->SetNumber(mass_->GetMassX() - 1, mass_->GetMassY(), 1);

				count_->AddCount(-1);

			}

		}
		else {

			//隣のマスが空いていたら雲を吐き出す
			if (csvData_->GetNumber(mass_->GetMassX() + 1, mass_->GetMassY()) == static_cast<int32_t>(TileName::kNone)) {

				Vector3 newPosition = { float(mass_->GetMassX() + 1) * 32.0f, -float(mass_->GetMassY()) * 32.0f, 1.0f };

				CloudManager::GetInstance()->GetDeadCloud()->SetPosition(newPosition);

				CloudManager::GetInstance()->GetDeadCloud()->SetIsActive(true);

				csvData_->SetNumber(mass_->GetMassX() + 1, mass_->GetMassY(), 1);

				count_->AddCount(-1);

			}

		}

		//フラグ降ろす
		isRemove_ = false;

	}

}

void RemoveCloudComp::Update()
{
}

void RemoveCloudComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void RemoveCloudComp::Load([[maybe_unused]]nlohmann::json& json)
{
}
