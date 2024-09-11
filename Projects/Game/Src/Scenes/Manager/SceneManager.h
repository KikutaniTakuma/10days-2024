#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <bitset>
#include <optional>
#include "Fade/Fade.h"
#include "Input/Input.h"
#include "BaseScene/BaseScene.h"
#include "SceneLoad/SceneLoad.h"

class SceneManager final {
public:
	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	~SceneManager() = default;

	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;

public:
	static void Initialize();
	static void InstanceReset();

	static SceneManager* const GetInstance();

private:
	static std::unique_ptr<SceneManager> instance_;
public:

	void Initialize(const std::string& sceneJsonFilePath);
	void Finalize();

	void SceneChange(const std::string& nextSceneJsonFilePath);

	void Update();

	void Draw();

public:
	bool IsEnd() const;


private:
	void UploadTextureData();


private:
	std::unique_ptr<Fade> fade_;

	class FrameInfo* frameInfo_ = nullptr;

	std::unique_ptr<SceneLoad> load_;

	std::string nextSceneJsonFilePath_;
};