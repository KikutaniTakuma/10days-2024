#include "EatCloudComp.h"
#include "TransformComp.h"
#include "Direction2DComp.h"
#include "CsvDataComp.h"
#include "Mass2DComp.h"
#include "CountComp.h"
#include "Input/Input.h"
#include "Game/TileName/TileName.h"
#include "AudioManager/AudioManager.h"

void EatCloudComp::Load() {
	AudioManager::GetInstance()->Load("./Resources/Sounds/SE_ingame_player_eat.mp3");
	eatAudio_ = AudioManager::GetInstance()->Get("./Resources/Sounds/SE_ingame_player_eat.mp3");
}

void EatCloudComp::FirstUpdate() {
	isStartAudio_ = false;

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

			//下に地面が無い(半分浮いている)場合
			if (csvData_->GetNumber(mass_->GetMassX(), mass_->GetMassY() + 1) == static_cast<int32_t>(TileName::kNone)) {

				//雲があれば食べて、カウントを増加させる
				if (auto cloud = CloudManager::GetInstance()->GetAliveCloud(mass_->GetMassX(), mass_->GetMassY())) {

					cloud->SetIsActive(false);
					csvData_->SetNumber(mass_->GetMassX(), mass_->GetMassY(), 0);

					count_->AddCount(1);
					isStartAudio_ = true;
				}

			}
			else {

				//隣に雲があれば食べて、カウントを増加させる
				if (auto cloud = CloudManager::GetInstance()->GetAliveCloud(mass_->GetMassX() - 1, mass_->GetMassY())) {

					cloud->SetIsActive(false);
					csvData_->SetNumber(mass_->GetMassX() - 1, mass_->GetMassY(), 0);

					count_->AddCount(1);
					isStartAudio_ = true;

				}

			}

		}
		else {

			//下に地面が無い(半分浮いている)場合
			if (csvData_->GetNumber(mass_->GetMassX(), mass_->GetMassY() + 1) == static_cast<int32_t>(TileName::kNone)) {

				//雲があれば食べて、カウントを増加させる
				if (auto cloud = CloudManager::GetInstance()->GetAliveCloud(mass_->GetMassX(), mass_->GetMassY())) {

					cloud->SetIsActive(false);
					csvData_->SetNumber(mass_->GetMassX(), mass_->GetMassY(), 0);

					count_->AddCount(1);
					isStartAudio_ = true;

				}

			}
			else {

				//隣に雲があれば食べて、カウントを増加させる
				if (auto cloud = CloudManager::GetInstance()->GetAliveCloud(mass_->GetMassX() + 1, mass_->GetMassY())) {

					cloud->SetIsActive(false);
					csvData_->SetNumber(mass_->GetMassX() + 1, mass_->GetMassY(), 0);

					count_->AddCount(1);
					isStartAudio_ = true;

				}

			}

		}

		isEat_ = false;

	}

}

void EatCloudComp::LastUpdate() {
	if (isStartAudio_) {
		eatAudio_->Start(0.3f, false);
	}
}

void EatCloudComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void EatCloudComp::Load([[maybe_unused]]nlohmann::json& json)
{
}
