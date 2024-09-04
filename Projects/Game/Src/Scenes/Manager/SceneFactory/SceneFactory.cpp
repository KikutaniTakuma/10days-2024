#include "SceneFactory.h"
#include "Scenes/TestScene/TestScene.h"

SceneFactory::SceneFactory():
	createScene_{}
{
	CreateFunctions();
}

SceneFactory* const SceneFactory::GetInstance() {
	static SceneFactory instance{};
	return &instance;
}

BaseScene* SceneFactory::CreateBaseScene(std::optional<BaseScene::ID> createSceneID) {
	return createScene_[createSceneID]();
}

void SceneFactory::CreateFunctions() {
	createScene_[BaseScene::ID::Game] =
		[]()->BaseScene* {
		return nullptr;
		};
	createScene_[BaseScene::ID::Title] =
		[]()->BaseScene* {
		return nullptr;
		};
	createScene_[BaseScene::ID::Result] =
		[]()->BaseScene* {
		return nullptr;
		};
	createScene_[BaseScene::ID::StageSelect] =
		[]()->BaseScene* {
		return nullptr;
		};
	createScene_[BaseScene::ID::Test] =
		[]()->BaseScene* {
		return new TestScene();
		};
}