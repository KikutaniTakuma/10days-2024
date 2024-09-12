#include "SceneChangeComp.h"
#include "Scenes/Manager/SceneManager.h"

void SceneChangeComp::Init() {
	EventComp::Init();
    sceneManager_ = SceneManager::GetInstance();
}

void SceneChangeComp::Event() {
	EventComp::Event();

	if (isEvent and not nextSceneJsonFileName_.empty()) {
		sceneManager_->SceneChange(nextSceneJsonFileName_);
	}
}

void SceneChangeComp::SetNextScene(const std::string& nextSceneJsonFileName) {
	nextSceneJsonFileName_ = nextSceneJsonFileName;
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

void SceneChangeComp::Debug([[maybe_unused]]const std::string& guiName) {
#ifdef _DEBUG
	if (ImGui::TreeNode(guiName.c_str())) {
        ImGui::Text("next scene : %s", nextSceneJsonFileName_.c_str());
        if (ImGui::Button("シーン切り替え")) {
            if (not nextSceneJsonFileName_.empty()) {
                sceneManager_->SceneChange(nextSceneJsonFileName_);
            }
        }

        if (ImGui::Button("ファイルパス再読み込み")) {
            size_t size = filePaths_.size();
            filePaths_.clear();
            filePaths_.reserve(size);
            filePaths_ = Lamb::GetFilePathFormDir("./SceneData/", ".json");
        }

        if (ImGui::TreeNode("テクスチャ読み込み")) {
            for (auto itr = filePaths_.begin(); itr != filePaths_.end(); itr++) {
                if (ImGui::Button(itr->string().c_str())) {
                    nextSceneJsonFileName_ = itr->string();
                }
            }
            ImGui::TreePop();
        }

		ImGui::TreePop();
	}
#endif // _DEBUG
}
