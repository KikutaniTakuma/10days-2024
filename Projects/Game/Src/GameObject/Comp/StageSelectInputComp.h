#pragma once
#include "../Object.h"

class StageSelectInputComp : public IComp {
public:

	using IComp::IComp;

	~StageSelectInputComp() = default;

	void Init() override;

	void Move() override;

	void Debug(const std::string& guiName) override;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	static int32_t stageNumber_;

	static constexpr int32_t kMaxStage_ = 10;

private:

	Lamb::SafePtr<class SceneChangeComp> sceneChangeComp_;

};
