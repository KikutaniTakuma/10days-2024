#include "SceneChangeComp.h"
#include "Scenes/Manager/SceneManager.h"

void SceneChangeComp::Init() {
	EventComp::Init();
}

void SceneChangeComp::Event() {
	EventComp::Event();

	if (isEvent) {
		//sceneManager_->SceneChange(nextID_);
	}
}

void SceneChangeComp::SetNextScene(const std::string& nextSceneJsonFileName) {
	nextSceneJsonFileName_ = nextSceneJsonFileName;
}

void SceneChangeComp::SetSceneManager(SceneManager* sceneManager)
{
	sceneManager_ = sceneManager;
}

void SceneChangeComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
	json["nextID"] = nextSceneJsonFileName_;
}

void SceneChangeComp::Load(nlohmann::json& json)
{
	nextSceneJsonFileName_ = json["nextID"].get<std::string>();
}
