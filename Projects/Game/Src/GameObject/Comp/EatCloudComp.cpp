#include "EatCloudComp.h"
#include "TransformComp.h"
#include "Direction2DComp.h"
#include "CsvDataComp.h"
#include "Mass2DComp.h"
#include "CountComp.h"
#include "Input/Input.h"

void EatCloudComp::FirstUpdate()
{

	Lamb::SafePtr gamepad = Input::GetInstance()->GetGamepad();
	Lamb::SafePtr key = Input::GetInstance()->GetKey();
	Lamb::SafePtr mouse = Input::GetInstance()->GetMouse();

}

void EatCloudComp::Init()
{
	transform_ = object_.AddComp<TransformComp>();
	direction_ = object_.AddComp<Direction2DComp>();
	csvData_ = object_.AddComp<CsvDataComp>();
	mass_ = object_.AddComp<Mass2DComp>();
	count_ = object_.AddComp<CountComp>();
}

void EatCloudComp::Event()
{

	if (isEat_) {

		//左を向いている場合
		if (direction_->IsLeft()) {

			//隣に雲があれば食べて、カウントを増加させる
			if (auto cloud = CloudManager::GetInstance()->GetAliveCloud(mass_->GetMassX() - 1, mass_->GetMassY())) {

				cloud->SetIsActive(false);
				csvData_->SetNumber(mass_->GetMassX() - 1, mass_->GetMassY(), 0);

				count_->AddCount(1);

			}

		}
		else {

			if (auto cloud = CloudManager::GetInstance()->GetAliveCloud(mass_->GetMassX() + 1, mass_->GetMassY())) {

				cloud->SetIsActive(false);
				csvData_->SetNumber(mass_->GetMassX() + 1, mass_->GetMassY(), 0);

				count_->AddCount(1);

			}

		}

		isEat_ = false;

	}

}

void EatCloudComp::Update()
{

}

void EatCloudComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void EatCloudComp::Load([[maybe_unused]]nlohmann::json& json)
{
}
