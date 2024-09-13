#include "UINumSpriteComp.h"
#include "SpriteRenderDataComp.h"
#include "UIDrawComp.h"
#include "StageSelectInputComp.h"
#include "UITransformComp.h"

void UINumSpriteComp::Init()
{
	spriteRenderDataComp_ = object_.AddComp<SpriteRenderDataComp>();
	UIDraw_ = object_.AddComp<UIDrawComp>();
	transform_ = object_.AddComp<UITransformComp>();
}

void UINumSpriteComp::Event()
{

	if (transform_->scale.x < defaultScale_) {

		transform_->scale.x += addValue_;

		if (transform_->scale.x > defaultScale_) {
			transform_->scale.x = defaultScale_;
		}

	}

	//ステージの数字を割り、その分UVのオフセットを移動させる。更新しない場合は動かさない
	if (divide_ != 0 and isUpdate_) {

		offset_ = StageSelectInputComp::stageNumber_ / divide_;

		spriteRenderDataComp_->uvTransform.translate.x = float(offset_) * 0.1f;

	}

	if (preOffset_ != offset_) {

		transform_->scale.x = smaleScale_;

	}

	preOffset_ = offset_;

}

void UINumSpriteComp::Debug([[maybe_unused]] const std::string& guiName)
{

#ifdef _DEBUG

	if (ImGui::TreeNode(guiName.c_str())) {
		ImGui::DragInt("割る数", &divide_, 0.1f, 1, 1000);
		ImGui::TreePop();
	}

#endif // _DEBUG


}

void UINumSpriteComp::Save(nlohmann::json& json) {
	SaveCompName(json);
	json["divide"] = divide_;
}

void UINumSpriteComp::Load([[maybe_unused]] nlohmann::json& json) {
	divide_ = json["divide"].get<int32_t>();
}

