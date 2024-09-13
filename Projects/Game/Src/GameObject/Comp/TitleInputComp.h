#pragma once
#include "../Object.h"

class TitleInputComp : public IComp {
public:

	using IComp::IComp;

	~TitleInputComp() = default;

	void Init() override;

	void Move() override;

	void Debug(const std::string& guiName) override;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	Lamb::SafePtr<class SceneChangeComp> sceneChangeComp_;

	Lamb::SafePtr<class Audio> pushButtonAudio_;

};
