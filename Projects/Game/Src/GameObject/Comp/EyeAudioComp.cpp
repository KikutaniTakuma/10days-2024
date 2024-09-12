#include "EyeAudioComp.h"
#include "EyeComp.h"

void EyeAudioComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
	json["aimVolume"] = aimVolume_;
	json["chargeVolume"] = chargeVolume_;
	json["fireVolume"] = fireVolume_;
}

void EyeAudioComp::Load([[maybe_unused]]nlohmann::json& json) {
	aimVolume_ = json["aimVolume"].get<float>();
	chargeVolume_ = json["chargeVolume"].get<float>();
	fireVolume_ = json["fireVolume"].get<float>();
}

void EyeAudioComp::Init() {
	eyeComp_ = object_.AddComp<EyeComp>();

	Lamb::SafePtr audioManager = AudioManager::GetInstance();
	audioManager->Load("./Resources/Sounds/SE_ingame_enemy_alarm.mp3");
	audioManager->Load("./Resources/Sounds/SE_ingame_enemy_charge.mp3");
	audioManager->Load("./Resources/Sounds/SE_ingame_enemy_attack.mp3");
	
	
	aimAudio_ = audioManager->Get("./Resources/Sounds/SE_ingame_enemy_alarm.mp3");
	chargeAudio_ = audioManager->Get("./Resources/Sounds/SE_ingame_enemy_charge.mp3");
	fireAudio_ = audioManager->Get("./Resources/Sounds/SE_ingame_enemy_attack.mp3");
}

void EyeAudioComp::Draw() {
	if (eyeComp_->IsAiming() and not aimAudio_->IsStart()) {
		aimAudio_->Start(aimVolume_, true);
	}
	else if(not eyeComp_->IsAiming()){
		aimAudio_->Stop();
	}

	if (eyeComp_->IsAimFixed() and not chargeAudio_->IsStart()) {
		chargeAudio_->Start(chargeVolume_, true);
	}
	else if (not eyeComp_->IsAimFixed()) {
		chargeAudio_->Stop();
	}

	if (eyeComp_->IsFire() and not fireAudio_->IsStart()) {
		fireAudio_->Start(fireVolume_, true);
	}
	else if(not eyeComp_->IsFire()){
		fireAudio_->Stop();
	}

}

void EyeAudioComp::Debug([[maybe_unused]]const std::string& guiName) {
#ifdef _DEBUG
	if(ImGui::TreeNode(guiName.c_str())){
		ImGui::DragFloat("aimVolume", &aimVolume_);
		ImGui::DragFloat("chargeVolume", &chargeVolume_);
		ImGui::DragFloat("fireVolume", &fireVolume_);

		ImGui::TreePop();
	}
#endif // _DEBUG
}
