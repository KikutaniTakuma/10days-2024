#include "SceneManager.h"

#include "Engine/EngineUtils/FrameInfo/FrameInfo.h"
#include "Engine/Graphics/TextureManager/TextureManager.h"

#include "Engine/Engine.h"

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

	load_ = std::make_unique<SceneLoad>();

	Engine::FrameStart();

	// ロード中の描画を開始
	load_->Start();

	objectManager_ = ObjectManager::GetInstance();
	objectManager_->Load(sceneJsonFilePath);

	// テクスチャデータのアップロード
	UploadTextureData();

	// ロード中の描画を終了
	load_->Stop();
}

void SceneManager::SceneChange(const std::string& nextSceneJsonFilePath) {
	if (not nextSceneJsonFilePath_.empty() or fade_->InEnd()
		or fade_->OutEnd() or fade_->IsActive()
		)
	{
		return;
	}
	nextSceneJsonFilePath_ = nextSceneJsonFilePath;

	fade_->OutStart();
}

void SceneManager::Update() {
	// オブジェクトマネージャー更新処理
	objectManager_->Update();

	// フェードの更新処理
	fade_->Update();

	if (fade_->OutEnd()) {
		// ロード中の描画を開始
		load_->Start();

#pragma region ロード中
		// オブジェクトマネージャーのロード処理
		objectManager_->Load(nextSceneJsonFilePath_);

		// ロード中の描画を終了
		load_->Stop();

		// フレーム処理開始
		Engine::FrameStart();
#pragma endregion

#pragma region その後の処理
		// ファイルパス削除
		nextSceneJsonFilePath_.clear();

		// フェードスタート
		fade_->InStart();

		// オブジェクトマネージャー更新処理
		objectManager_->Update();
#pragma endregion
	}

	// テクスチャデータのアップロード
	UploadTextureData();
}

void SceneManager::Draw() {
	// オブジェクトマネージャーの描画処理
	objectManager_->Draw();
}

void SceneManager::UploadTextureData()
{
	auto textureManager = TextureManager::GetInstance();
	// このフレームで画像読み込みが発生していたらTextureをvramに送る
	textureManager->UploadTextureData();
	// dramから解放
	textureManager->ReleaseIntermediateResource();
}

void SceneManager::Finalize() {
	if (load_) {
		load_.reset();
	}


	fade_.reset();
}
