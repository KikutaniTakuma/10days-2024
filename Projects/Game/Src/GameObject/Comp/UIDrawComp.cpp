#include "UIDrawComp.h"
#include "Utils/EngineInfo.h"
#include "Drawers/DrawerManager.h"
#include "../Comp/UISpriteRenderDataComp.h"
#include "../Comp/UITransformComp.h"
#include "Camera/Camera.h"

void UIDrawComp::Init()
{
	tex2D_ = DrawerManager::GetInstance()->GetTexture2D();
	renderDataComp_ = object_.AddComp<UISpriteRenderDataComp>();
	transformComp_ = object_.AddComp<UITransformComp>();
}

void UIDrawComp::Event()
{
}

void UIDrawComp::Draw()
{
	Vector2 clientSize = Lamb::ClientSize();
	Mat4x4 cameraMatrix = Mat4x4::MakeTranslate(Vector3::kZIdentity * 10.0f) * Camera::GetStaticViewOthographics();

	tex2D_->Draw(
		renderDataComp_->GetOffsetMatrix() * transformComp_->GetWorldMatrix(),
		renderDataComp_->uvTransform.GetMatrix(),
		cameraMatrix,
		renderDataComp_->texHandle,
		renderDataComp_->color.GetColorRGBA(),
		renderDataComp_->type
	);
}

void UIDrawComp::Save([[maybe_unused]] nlohmann::json& json)
{
	SaveCompName(json);
}

void UIDrawComp::Load([[maybe_unused]] nlohmann::json& json)
{
}
