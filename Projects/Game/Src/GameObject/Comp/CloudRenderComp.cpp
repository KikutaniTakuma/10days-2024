#include "CloudRenderComp.h"
#include "SpriteRenderDataComp.h"
#include "Utils/Random.h"

void CloudRenderComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void CloudRenderComp::Load([[maybe_unused]]nlohmann::json& json) {

}

void CloudRenderComp::Init() {
	spriteRenderDataComp_ = object_.AddComp<SpriteRenderDataComp>();
}

void CloudRenderComp::FirstUpdate()
{
	if (not isFirstUpdate_) {
		spriteRenderDataComp_->uvTransform.scale.x = 1.0f / 4.0f;
		spriteRenderDataComp_->uvTransform.translate.x = 1.0f / 4.0f * static_cast<float>(Lamb::Random(0u, 3u));

		isFirstUpdate_ = true;
	}
}

void CloudRenderComp::Debug([[maybe_unused]]const std::string& guiName)
{
#ifdef _DEBUG
	if(ImGui::TreeNode(guiName.c_str())){
		if (ImGui::Button("ランダム")) {
			spriteRenderDataComp_->uvTransform.scale.x = 1.0f / 4.0f;
			spriteRenderDataComp_->uvTransform.translate.x = 1.0f / 4.0f * static_cast<float>(Lamb::Random(0u, 3u));
		}

		ImGui::TreePop();
	}
#endif // _DEBUG

}
