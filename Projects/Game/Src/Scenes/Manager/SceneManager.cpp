#include "SceneManager.h"
#include "Input/Input.h"
#include "SceneFactory/SceneFactory.h"

#include "Engine/EngineUtils/FrameInfo/FrameInfo.h"
#include "Engine/Graphics/TextureManager/TextureManager.h"
#include "Engine/Graphics/RenderContextManager/RenderContextManager.h"

#include "imgui.h"

std::unique_ptr<SceneManager> SceneManager::instance_;

void SceneManager::Initialize()
{
	instance_ = std::make_unique<SceneManager>();
}

void SceneManager::InstanceReset()
{
	instance_.reset();
}

SceneManager* const SceneManager::GetInstance()
{
	return instance_.get();
}

void SceneManager::Initialize(const std::string& sceneJsonFilePath) {
	fade_ = std::make_unique<Fade>();

	frameInfo_ = FrameInfo::GetInstance();
	SceneFactory* const sceneFactory = SceneFactory::GetInstance();

	load_ = std::make_unique<SceneLoad>();

	// テクスチャデータのアップロード
	UploadTextureData();

}

void SceneManager::SceneChange(const std::string& nextSceneJsonFilePath) {
	if (not nextSceneJsonFilePath_.empty() || fade_->InEnd()
		|| fade_->OutEnd() || fade_->IsActive()
		)
	{
		return;
	}
	nextSceneJsonFilePath_ = nextSceneJsonFilePath;

	fade_->OutStart();
}

void SceneManager::Update() {
	if (input_->GetGamepad()->PushAnyKey()) {
		isPad_ = true;
	}
	else if (input_->GetMouse()->PushAnyKey() || input_->GetKey()->PushAnyKey()) {
		isPad_ = false;
	}


	if (scene_ && !next_) {
#ifdef _DEBUG
		scene_->ChangeCamera();
#endif // _DEBUG

		scene_->Update();
		Debug();
	}

	// フェードの更新処理
	fade_->Update();



	if (fade_->OutEnd()) {
		// ロード中の描画を開始
		//load_->Start();

#pragma region シーン切り替え
		// 前のシーンのIDを保存
		preSceneID_ = scene_->GetID();

		// シーン終わり処理
		scene_->Finalize();
		// 次のシーンへ
		scene_.reset(next_.release());
		// 次のシーンを格納するユニークポインタをリセット
		next_.reset();
#pragma endregion

#pragma region ロード中
		scene_->Load();

		// シーンの初期化
		scene_->Initialize();


		// ロード中の描画を終了
		//load_->Stop();
#pragma endregion

#pragma region その後の処理
		// フェードスタート
		fade_->InStart();

		// シーンの更新処理
		scene_->Update();
#pragma endregion
	}

	// テクスチャデータのアップロード
	UploadTextureData();
}

void SceneManager::Draw() {
	if (scene_) {
		scene_->Draw();
	}
}

bool SceneManager::IsEnd() const {
	if (!scene_) {
		return true;
	}

	return scene_->GetID() == finishID_ &&
		(input_->GetKey()->Pushed(DIK_ESCAPE) /*||
			input_->GetGamepad()->Pushed(Gamepad::Button::START)*/);
}

const Camera& SceneManager::GetCurrentSceneCamera() const
{
	return scene_->GetCamera();
}

BaseScene::ID SceneManager::GetCurrentSceneID() const
{
	return scene_->GetID();
}

BaseScene::ID SceneManager::GetPreSceneID() const
{
	return preSceneID_.value();
}

void SceneManager::UploadTextureData()
{
	auto textureManager = TextureManager::GetInstance();
	// このフレームで画像読み込みが発生していたらTextureをvramに送る
	textureManager->UploadTextureData();
	// dramから解放
	textureManager->ReleaseIntermediateResource();
}

void SceneManager::Initialize(const std::string& sceneJsonFilePath)
{
}

void SceneManager::Finalize() {
	if (load_) {
		load_.reset();
	}


	fade_.reset();
}

void SceneManager::SceneChange(const std::string& nextSceneJsonFilePath)
{
}
