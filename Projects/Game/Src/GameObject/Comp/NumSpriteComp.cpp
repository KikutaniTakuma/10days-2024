#include "NumSpriteComp.h"
#include "SpriteRenderDataComp.h"
#include "SpriteRenderComp.h"
#include "StageSelectInputComp.h"
#include "TransformComp.h"

void NumSpriteComp::Init()
{
	spriteRenderDataComp_ = object_.AddComp<SpriteRenderDataComp>();
	spriteRenderComp_ = object_.AddComp<SpriteRenderComp>();
	transform_ = object_.AddComp<TransformComp>();
}

void NumSpriteComp::Event()
{

	if (transform_->scale.x < defaultScale_) {

		transform_->scale.x += addValue_;

		if (transform_->scale.x > defaultScale_) {
			transform_->scale.x = defaultScale_;
		}

	}

	//ステージの数字を割り、その分UVのオフセットを移動させる
	if (divide_ != 0) {

		offset_ = StageSelectInputComp::stageNumber_ / divide_;

		spriteRenderDataComp_->uvTransform.translate.x = float(offset_) * 0.1f;

	}

	if (preOffset_ != offset_) {
		
		transform_->scale.x = smaleScale_;

	}

	preOffset_ = offset_;

}

void NumSpriteComp::Debug([[maybe_unused]] const std::string& guiName)
{

#ifdef _DEBUG

	if (ImGui::TreeNode(guiName.c_str())) {
		ImGui::DragInt("割る数", &divide_, 0.1f, 1, 1000);
		ImGui::TreePop();
	}

#endif // _DEBUG


}

void NumSpriteComp::Save(nlohmann::json& json) {
	SaveCompName(json);
	json["divide"] = divide_;
}

void NumSpriteComp::Load([[maybe_unused]] nlohmann::json& json) {
	divide_ = json["divide"].get<int32_t>();
}

