#include "RemoveCloudComp.h"
#include "TransformComp.h"
#include "Direction2DComp.h"
#include "CsvDataComp.h"
#include "Mass2DComp.h"
#include "CountComp.h"
#include "Game/TileName/TileName.h"
#include "Input/Input.h"
#include "AudioManager/AudioManager.h"

void RemoveCloudComp::Load() {
	AudioManager::GetInstance()->Load("./Resources/Sounds/SE_ingame_player_outPut.mp3");
	removeCloudAudio_ = AudioManager::GetInstance()->Get("./Resources/Sounds/SE_ingame_player_outPut.mp3");
}

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

	isStartAudio_ = false;

}

void RemoveCloudComp::Event()
{

	//吐き出しフラグが立っていたら
	if (isRemove_) {

		if (direction_->IsLeft()) {

			//半分浮いている場合
			if (csvData_->GetNumber(mass_->GetMassX(), mass_->GetMassY() + 1) == static_cast<int32_t>(TileName::kNone)) {

				//マスが空いていたら雲を吐き出す
				if (csvData_->GetNumber(mass_->GetMassX(), mass_->GetMassY()) == static_cast<int32_t>(TileName::kNone) or
					csvData_->GetNumber(mass_->GetMassX(), mass_->GetMassY()) == static_cast<int32_t>(TileName::kPlayer)) {

					Vector3 newPosition = { float(mass_->GetMassX()) * 32.0f, -float(mass_->GetMassY()) * 32.0f, 5.0f };

					CloudManager::GetInstance()->GetDeadCloud()->SetPosition(newPosition);

					CloudManager::GetInstance()->GetDeadCloud()->SetIsActive(true);

					csvData_->SetNumber(mass_->GetMassX(), mass_->GetMassY(), 1);

					count_->AddCount(-1);
					isStartAudio_ = true;
				}

			}
			else {

				//隣のマスが空いていたら雲を吐き出す
				if (csvData_->GetNumber(mass_->GetMassX() - 1, mass_->GetMassY()) == static_cast<int32_t>(TileName::kNone) or
					csvData_->GetNumber(mass_->GetMassX() - 1, mass_->GetMassY()) == static_cast<int32_t>(TileName::kPlayer)) {

					Vector3 newPosition = { float(mass_->GetMassX() - 1) * 32.0f, -float(mass_->GetMassY()) * 32.0f, 5.0f };

					CloudManager::GetInstance()->GetDeadCloud()->SetPosition(newPosition);

					CloudManager::GetInstance()->GetDeadCloud()->SetIsActive(true);

					csvData_->SetNumber(mass_->GetMassX() - 1, mass_->GetMassY(), 1);

					count_->AddCount(-1);
					isStartAudio_ = true;
				}

			}

		}
		else {

			//半分浮いている場合
			if (csvData_->GetNumber(mass_->GetMassX(), mass_->GetMassY() + 1) == static_cast<int32_t>(TileName::kNone)) {

				//マスが空いていたら雲を吐き出す
				if (csvData_->GetNumber(mass_->GetMassX(), mass_->GetMassY()) == static_cast<int32_t>(TileName::kNone) or
					csvData_->GetNumber(mass_->GetMassX(), mass_->GetMassY()) == static_cast<int32_t>(TileName::kPlayer)) {

					Vector3 newPosition = { float(mass_->GetMassX()) * 32.0f, -float(mass_->GetMassY()) * 32.0f, 5.0f };

					CloudManager::GetInstance()->GetDeadCloud()->SetPosition(newPosition);

					CloudManager::GetInstance()->GetDeadCloud()->SetIsActive(true);

					csvData_->SetNumber(mass_->GetMassX(), mass_->GetMassY(), 1);

					count_->AddCount(-1);
					isStartAudio_ = true;
				}

			}
			else {

				//隣のマスが空いていたら雲を吐き出す
				if (csvData_->GetNumber(mass_->GetMassX() + 1, mass_->GetMassY()) == static_cast<int32_t>(TileName::kNone) or
					csvData_->GetNumber(mass_->GetMassX() + 1, mass_->GetMassY()) == static_cast<int32_t>(TileName::kPlayer)) {

					Vector3 newPosition = { float(mass_->GetMassX() + 1) * 32.0f, -float(mass_->GetMassY()) * 32.0f, 5.0f };

					CloudManager::GetInstance()->GetDeadCloud()->SetPosition(newPosition);

					CloudManager::GetInstance()->GetDeadCloud()->SetIsActive(true);

					csvData_->SetNumber(mass_->GetMassX() + 1, mass_->GetMassY(), 1);

					count_->AddCount(-1);
					isStartAudio_ = true;
				}

			}

		}

		//フラグ降ろす
		isRemove_ = false;

	}

}
void RemoveCloudComp::LastUpdate() {
	if (isStartAudio_) {
		removeCloudAudio_->Start(0.3f, false);
	}
}
void RemoveCloudComp::Finalize() {
	if (isStartAudio_) {
		removeCloudAudio_->Stop();
	}
}
void RemoveCloudComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void RemoveCloudComp::Load([[maybe_unused]]nlohmann::json& json)
{
}
