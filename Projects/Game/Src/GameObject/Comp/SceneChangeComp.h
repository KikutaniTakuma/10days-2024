#pragma once
#include "../Object.h"


class SceneChangeComp : public IComp {
public:
	using IComp::IComp;

	~SceneChangeComp() = default;

public:
	void Init() override;

	void LastUpdate() override;

	void SetNextScene(const std::string& nextSceneJsonFileName);

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	void Debug(const std::string& guiName) override;

private:
	std::string nextSceneJsonFileName_;
	Lamb::SafePtr<class SceneManager> sceneManager_;

	Lamb::SafePtr<class EventComp> eventComp_;

#ifdef _DEBUG
	std::vector<std::filesystem::path> filePaths_;
#endif // _DEBUG

};
