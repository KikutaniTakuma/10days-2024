#pragma once
#include "../Object.h"

#include "AudioManager/AudioManager.h"

class EyeAudioComp : public IComp {
public:
	using IComp::IComp;

	~EyeAudioComp() = default;

public:
	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

public:
	void Init() override;

	void Draw() override;

	void Debug(const std::string& guiName);
private:
	Lamb::SafePtr<Audio> aimAudio_;
	Lamb::SafePtr<Audio> chargeAudio_;
	Lamb::SafePtr<Audio> fireAudio_;

	float aimVolume_ = 1.0f;
	float chargeVolume_ = 1.0f;
	float fireVolume_ = 1.0f;
	
	Lamb::SafePtr<class EyeComp> eyeComp_;
};
