#include "TextureHandlesComp.h"
#include "Engine/Graphics/TextureManager/TextureManager.h"

void TextureHandlesComp::Init()
{
}

void TextureHandlesComp::Save(nlohmann::json& json) {
	SaveCompName(json);
	json["fileNames"] = nlohmann::json::array();
	for (size_t i = 0; i < fileNames_.size(); i++) {
		json["fileNames"].push_back(fileNames_[i]);
	}
}

void TextureHandlesComp::Load([[maybe_unused]] nlohmann::json& json) {
	for (size_t i = 0; i < json["fileNames"].size(); i++) {
		fileNames_.push_back(json["fileNames"][i]);
		Lamb::SafePtr textureManager = TextureManager::GetInstance();
		textureManager->LoadTexture(fileNames_[i]);
		textureHandles_.push_back(textureManager->GetHandle(fileNames_[i]));
	}
}

