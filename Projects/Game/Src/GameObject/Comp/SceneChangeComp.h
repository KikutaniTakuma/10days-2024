#pragma once
#include "EventComp.h"


class SceneChangeComp : public EventComp {
public:
	using EventComp::EventComp;

	~SceneChangeComp() = default;

public:
	void Init() override;

	void Event() override;

	void SetNextScene(const std::string& nextSceneJsonFileName);

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	void Debug(const std::string& guiName) override;
private:
	std::string nextSceneJsonFileName_;
	Lamb::SafePtr<class SceneManager> sceneManager_;

#ifdef _DEBUG
	std::vector<std::filesystem::path> filePaths_;
#endif // _DEBUG

};
