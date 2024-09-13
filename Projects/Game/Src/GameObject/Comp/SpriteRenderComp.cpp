#include "SpriteRenderComp.h"
#include "Drawers/DrawerManager.h"
#include "SpriteRenderDataComp.h"
#include "Drawers/Texture2D/Texture2D.h"

#include "TransformComp.h"
#include "CameraComp.h"

void SpriteRenderComp::Init() {
	transformComp_ = object_.AddComp<TransformComp>();
	renderDataComp_ = object_.AddComp<SpriteRenderDataComp>();

	tex2D_ = DrawerManager::GetInstance()->GetTexture2D();
}

void SpriteRenderComp::Draw(CameraComp* cameraComp) {
	if (isDraw) {
		tex2D_->Draw(
			renderDataComp_->GetOffsetMatrix() * renderDataComp_->GetUserOffsetMatrix() * transformComp_->GetWorldMatrix(),
			renderDataComp_->uvTransform.GetMatrix(),
			cameraComp->GetCameraMatrix(),
			renderDataComp_->texHandle,
			renderDataComp_->color.GetColorRGBA(),
			renderDataComp_->type
		);
	}
}

void SpriteRenderComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void SpriteRenderComp::Load([[maybe_unused]]nlohmann::json& json)
{
}

void SpriteRenderComp::Debug([[maybe_unused]]const std::string& guiName) {
#ifdef _DEBUG
	if (ImGui::TreeNode(guiName.c_str())) {
		ImGui::Checkbox("描画有効", &isDraw);

		ImGui::TreePop();
	}
#endif // _DEBUG
}

