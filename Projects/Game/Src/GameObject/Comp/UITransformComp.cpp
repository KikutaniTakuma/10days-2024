#include "UITransformComp.h"
#include "../Manager/TransformCompUpdater.h"
#ifdef _DEBUG
#include "Camera/Camera.h"
#include "imgui.h"
#endif // _DEBUG

#ifdef _DEBUG
const std::array<std::pair<std::string, ImGuizmo::OPERATION>, 5> UITransformComp::kGuizmoMode_ = {
	std::make_pair<std::string, ImGuizmo::OPERATION>("TRANSLATE", ImGuizmo::TRANSLATE),
	std::make_pair<std::string, ImGuizmo::OPERATION>("ROTATE", ImGuizmo::ROTATE),
	std::make_pair<std::string, ImGuizmo::OPERATION>("SCALE", ImGuizmo::SCALE),
	std::make_pair<std::string, ImGuizmo::OPERATION>("SCALEU", ImGuizmo::SCALEU),
	std::make_pair<std::string, ImGuizmo::OPERATION>("UNIVERSAL", ImGuizmo::UNIVERSAL)
};
#endif // _DEBUG



UITransformComp::UITransformComp(Object* const object) :
	IComp(object),
	scale(Vector3::kIdentity),
	rotate(),
	translate(),
	worldMatrix_(Mat4x4::kIdentity),
	parent_(nullptr),
	children_()
{
	TransformCompUpdater::GetInstance()->Set(this);
}

UITransformComp::~UITransformComp()
{
	TransformCompUpdater::GetInstance()->Erase(this);
}

void UITransformComp::Init()
{

}

void UITransformComp::UpdateMatrix() {
#ifdef _DEBUG
	rotate.SetEuler(eulerRotate);
#endif // _DEBUG
	rotate = rotate.Normalize();
	worldMatrix_ = Mat4x4::MakeAffin(scale, rotate, translate);
}

void UITransformComp::UpdateChildrenMatrix() {
	for (auto& i : children_) {
		i->UpdateParentMatrix();
		if (i->HaveChildren()) {
			i->UpdateChildrenMatrix();
		}
	}
}

void UITransformComp::UpdateParentMatrix()
{
	if (parent_.have()) {
		worldMatrix_ *= parent_->worldMatrix_;
	}
}

void UITransformComp::SetParent(Lamb::SafePtr<UITransformComp> parent)
{
	// もしparent_がnullじゃないかつ、今もっているやつと違うものかつ、親のchildrenに自身を持っているか
	if (parent_.have() and parent_ != parent and parent_->children_.contains(this)) {
		parent_->children_.erase(this);
	}
	parent_ = parent;
	if (parent_.have()) {
		parent_->children_.insert(this);
	}
}

void UITransformComp::Debug([[maybe_unused]] const std::string& guiName) {
#ifdef _DEBUG
	if (ImGui::TreeNode((guiName + " Guizmo").c_str())) {
		// コンボボックスを使ってenumの値を選択する
		if (ImGui::BeginCombo("BlendType", kGuizmoMode_[guimoType_].first.c_str()))
		{
			for (uint32_t count = 0; auto & i : kGuizmoMode_)
			{
				bool isSelected = (guimoType_ == count);
				if (ImGui::Selectable(i.first.c_str(), isSelected))
				{
					guimoType_ = count;
				}
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
				count++;
			}
			ImGui::EndCombo();
		}
		isGuizmo_ = true;

		ImGui::TreePop();
	}
	else {
		isGuizmo_ = false;
	}
	if (ImGui::TreeNode(guiName.c_str())) {
		ImGui::DragFloat3("scale", scale.data(), 0.01f);

		eulerRotate = rotate.ToEuler();
		eulerRotate *= Lamb::Math::kToDegree<float32_t>;
		ImGui::DragFloat3("rotate(Degree)", eulerRotate.data(), 1.0f);
		eulerRotate *= Lamb::Math::kToRadian<float32_t>;
		rotate = Quaternion::EulerToQuaternion(eulerRotate);

		ImGui::DragFloat3("translate", translate.data(), 0.01f);
		for (size_t index = 0; auto & i : children_) {
			i->Debug("children_" + std::to_string(index));
			index++;
		}

		ImGui::TreePop();
	}
#endif // _DEBUG

}

#ifdef _DEBUG
void UITransformComp::SetGuizmoID(uint32_t id) {
	guizmoID_ = id;
}

void UITransformComp::Guizmo() {
	if (isGuizmo_) {
		ImGuizmo::SetID(guizmoID_);
		const Mat4x4& view = Mat4x4::MakeTranslate(Vector3::kZIdentity * 20.0f);
		const Mat4x4& ndc = Camera::GetStaticViewOthographics();
		if (ImGuizmo::Manipulate(view.data(), ndc.data(), kGuizmoMode_[guimoType_].second, ImGuizmo::WORLD, worldMatrix_.data())) {
			if (parent_) {
#ifdef _DEBUG
				(worldMatrix_ * parent_->worldMatrix_.Inverse()).Decompose(scale, eulerRotate, translate);
#else
				(worldMatrix_ * parent_->worldMatrix_.Inverse()).Decompose(scale, rotate, translate);
#endif // _DEBUG
			}
			else {
#ifdef _DEBUG
				worldMatrix_.Decompose(scale, eulerRotate, translate);
#else
				worldMatrix_.Decompose(scale, rotate, translate);
#endif // _DEBUG

			}
			TransformCompUpdater::GetInstance()->SetCurretnGuizmoID(guizmoID_);
		}
	}
}
#endif // _DEBUG

void UITransformComp::Save(nlohmann::json& json) {
	SaveCompName(json);
	json["scale"] = nlohmann::json::array();
	for (auto& i : scale) {
		json["scale"].push_back(i);
	}
	json["rotate"] = nlohmann::json::array();
	for (auto& i : rotate) {
		json["rotate"].push_back(i);
	}
	json["translate"] = nlohmann::json::array();
	for (auto& i : translate) {
		json["translate"].push_back(i);
	}
}

void UITransformComp::Load(nlohmann::json& json)
{
	for (size_t i = 0; i < json["scale"].size(); i++) {
		scale[i] = json["scale"][i];
	}
	for (size_t i = 0; i < json["rotate"].size(); i++) {
		rotate.m[i] = json["rotate"][i];
	}
	for (size_t i = 0; i < json["translate"].size(); i++) {
		translate[i] = json["translate"][i];
	}

#ifdef _DEBUG
	eulerRotate = rotate.ToEuler();
#endif // _DEBUG

}
