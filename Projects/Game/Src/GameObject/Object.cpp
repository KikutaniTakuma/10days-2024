#include "Object.h"
#include "Utils/EngineInfo.h"
#include "Comp/ButtonComp.h"
#include "Comp/CameraComp.h"
#include "Comp/Camera3DComp.h"
#include "Comp/Camera2DComp.h"
#include "Comp/ChildrenObjectComp.h"
#include "Comp/CsvDataComp.h"
#include "Comp/EventComp.h"
#include "Comp/FallComp.h"
#include "Comp/InputMoveComp.h"
#include "Comp/JsonComp.h"
#include "Comp/ModelRenderComp.h"
#include "Comp/ModelRenderDataComp.h"
#include "Comp/ObbComp.h"
#include "Comp/ObbPushComp.h"
#include "Comp/QuadComp.h"
#include "Comp/SceneChangeComp.h"
#include "Comp/SpriteRenderComp.h"
#include "Comp/SpriteRenderDataComp.h"
#include "Comp/SpriteAnimatorComp.h"
#include "Comp/TransformComp.h"
#include "Comp/CloudComp.h"
#include "Comp/CloudRenderComp.h"
#include "Comp/FlagComp.h"
#include "Comp/PlayerComp.h"
#include "Comp/CountComp.h"
#include "Comp/Direction2DComp.h"
#include "Comp/EatCloudComp.h"
#include "Comp/RemoveCloudComp.h"
#include "Comp/Mass2DComp.h"
#include "Comp/JumpComp.h"
#include "Comp/Aabb2DComp.h"
#include "Comp/CollectionComp.h"
#include "Comp/FollowCamera2DComp.h"
#include "Comp/GoalComp.h"
#include "Comp/InvisibleComp.h"
#include "Comp/KeyComp.h"
#include "Comp/TextureHandlesComp.h"

#include "Comp/LineComp.h"
#include "Comp/LineRenderComp.h"
#include "Comp/LineRenderDataComp.h"
#include "Comp/LineCollisionComp.h"
#include "Comp/LineConvertTransformComp.h"

#include "Comp/EyeComp.h"
#include "Comp/EyeStateComp.h"
#include "Comp/EaseingComp.h"
#include "Comp/EyeAudioComp.h"

#include "Comp/AudioComp.h"
#include "Comp/BgmComp.h"

#include "Comp/InstanceTimeComp.h"

#include "Comp/UIDrawComp.h"
#include "Comp/UITransformComp.h"

#include "Comp/BackGroundComp.h"
#include "Comp/UvOperatorComp.h"

#include "Comp/TitleInputComp.h"
#include "Comp/StageSelectInputComp.h"
#include "Comp/ResultInputComp.h"

#include "Comp/EatCloudAnimationComp.h"

#include "Comp/NumSpriteComp.h"
#include "Comp/EasingSpriteComp.h"
#include "Comp/ArrowComp.h"
#include "Comp/CloudUIComp.h"
#include "Comp/SpriteUVChangeComp.h"

void Object::Init() {
	/*for (auto& i : components_) {
		i.second->Init();
	}*/
}

void Object::Finalize() {
	for (auto& i : components_) {
		i.second->Finalize();
	}
}

void Object::FirstUpdate()
{
	for (auto& i : components_) {
		i.second->FirstUpdate();
	}
}

void Object::Move()
{
	for (auto& i : components_) {
		i.second->Move();
	}
}

void Object::Event() {
	for (auto& i : components_) {
		i.second->Event();
	}
}

void Object::Update() {
	for (auto& i : components_) {
		i.second->Update();
	}
}

void Object::LastUpdate()
{
	for (auto& i : components_) {
		i.second->LastUpdate();
	}
}

void Object::Draw([[maybe_unused]] CameraComp* cameraComp) const
{
	for (auto& i : components_) {
		i.second->Draw(cameraComp);
	}
}

void Object::Draw() const {
	for (auto& i : components_) {
		i.second->Draw();
	}
}

bool Object::Debug([[maybe_unused]] const std::string& guiName) {
#ifdef _DEBUG
	if (ImGui::TreeNode(guiName.c_str())) {
		if (DebugAddComp()) {
			ImGui::TreePop();
			return true;
		}
		ImGui::Text("tags : ");
		ImGui::BeginChild(ImGui::GetID((void*)0), { 0.0f, 50.0f }, ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX, ImGuiWindowFlags_NoTitleBar);
		for (auto& i : tags_) {
			ImGui::Text("%s, ", i.second.c_str());
		}
		ImGui::EndChild();
		if (ImGui::TreeNode("componets")) {
			for (auto& i : components_) {
				i.second->Debug(tags_[i.first]);
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
#endif // _DEBUG

	return false;
}

bool Object::DebugAddComp() {
#ifdef _DEBUG
	if (ImGui::TreeNode("Comps")) {
		ImGui::BeginChild(ImGui::GetID((void*)0), { 0.0f, 150.0f }, ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX, ImGuiWindowFlags_NoTitleBar);
		DebugAdd<AudioComp>();
		DebugAdd<BgmComp>();
		DebugAdd<ButtonComp>();
		DebugAdd<Camera2DComp>();
		DebugAdd<Camera3DComp>();
		DebugAdd<ChildrenObjectComp>();
		DebugAdd<CsvDataComp>();
		DebugAdd<JsonComp>();
		DebugAdd<EventComp>();
		DebugAdd<FallComp>();
		DebugAdd<InputMoveComp>();
		DebugAdd<ModelRenderComp>();
		DebugAdd<ModelRenderDataComp>();
		DebugAdd<ObbComp>();
		DebugAdd<ObbPushComp>();
		DebugAdd<QuadComp>();
		DebugAdd<SceneChangeComp>();
		DebugAdd<SpriteRenderComp>();
		DebugAdd<SpriteRenderDataComp>();
		DebugAdd<SpriteAnimatorComp>();
		DebugAdd<TransformComp>();
		DebugAdd<FlagComp>();
		DebugAdd<CloudComp>();
		DebugAdd<CloudRenderComp>();
		DebugAdd<PlayerComp>();
		DebugAdd<CountComp>();
		DebugAdd<Direction2DComp>();
		DebugAdd<EatCloudComp>();
		DebugAdd<RemoveCloudComp>();
		DebugAdd<Mass2DComp>();
		DebugAdd<JumpComp>();
		DebugAdd<Aabb2DComp>();
		DebugAdd<CollectionComp>();
		DebugAdd<FollowCamera2DComp>();
		DebugAdd<GoalComp>();
		DebugAdd<InvisibleComp>();
		DebugAdd<KeyComp>();
		DebugAdd<LineComp>();
		DebugAdd<LineRenderComp>();
		DebugAdd<LineRenderDataComp>();
		DebugAdd<LineCollisionComp>();
		DebugAdd<LineConvertTransformComp>();
		DebugAdd<EyeComp>();
		DebugAdd<EyeStateComp>();
		DebugAdd<EyeAudioComp>();
		DebugAdd<EaseingComp>();
		DebugAdd<TextureHandlesComp>();
		DebugAdd<InstanceTimeComp>();
		DebugAdd<UIDrawComp>();
		DebugAdd<UITransformComp>();
		DebugAdd<BackGroundComp>();
		DebugAdd<UvOperatorComp>();
		DebugAdd<TitleInputComp>();
		DebugAdd<StageSelectInputComp>();
		DebugAdd<EatCloudAnimationComp>();
		DebugAdd<ResultInputComp>();
		DebugAdd<UvOperatorComp>();
		DebugAdd<NumSpriteComp>();
		DebugAdd<EasingSpriteComp>();
		DebugAdd<ArrowComp>();
		DebugAdd<CloudUIComp>();
		DebugAdd<SpriteUVChangeComp>();

		ImGui::EndChild();

		ImGui::TreePop();

		return true;
	}
#endif // _DEBUG

	return false;
}

void Object::Save(nlohmann::json& json) {
	json["type"] = "Object";
	json["Comps"] = nlohmann::json::array();
	for(auto& comp : this->components_) {
		json["Comps"].push_back(nlohmann::json::object());
		comp.second->Save(json["Comps"].back());
	}
}

void Object::Load(nlohmann::json& compData) {
	// コンポーネントを追加
	for (auto& comp : compData) {
		AddComps(comp);
	}

	for (auto& i : components_) {
		i.second->Load();
	}
}

void Object::AddComps(nlohmann::json& compData)
{
	std::string compName = compData["CompName"].get<std::string>();

	AddAndLoadComp<AudioComp>(compName, compData);
	AddAndLoadComp<BgmComp>(compName, compData);
	AddAndLoadComp<ButtonComp>(compName, compData);
	AddAndLoadComp<Camera2DComp>(compName, compData);
	AddAndLoadComp<Camera3DComp>(compName, compData);
	AddAndLoadComp<ChildrenObjectComp>(compName, compData);
	AddAndLoadComp<CsvDataComp>(compName, compData);
	AddAndLoadComp<JsonComp>(compName, compData);
	AddAndLoadComp<EventComp>(compName, compData);
	AddAndLoadComp<FallComp>(compName, compData);
	AddAndLoadComp<InputMoveComp>(compName, compData);
	AddAndLoadComp<ModelRenderComp>(compName, compData);
	AddAndLoadComp<ModelRenderDataComp>(compName, compData);
	AddAndLoadComp<ObbComp>(compName, compData);
	AddAndLoadComp<ObbPushComp>(compName, compData);
	AddAndLoadComp<QuadComp>(compName, compData);
	AddAndLoadComp<SceneChangeComp>(compName, compData);
	AddAndLoadComp<SpriteRenderComp>(compName, compData);
	AddAndLoadComp<SpriteRenderDataComp>(compName, compData);
	AddAndLoadComp<SpriteAnimatorComp>(compName, compData);
	AddAndLoadComp<TransformComp>(compName, compData);
	AddAndLoadComp<FlagComp>(compName, compData);
	AddAndLoadComp<CloudComp>(compName, compData);
	AddAndLoadComp<CloudRenderComp>(compName, compData);
	AddAndLoadComp<PlayerComp>(compName, compData);
	AddAndLoadComp<LineComp>(compName, compData);
	AddAndLoadComp<LineRenderComp>(compName, compData);
	AddAndLoadComp<LineRenderDataComp>(compName, compData);
	AddAndLoadComp<LineCollisionComp>(compName, compData);
	AddAndLoadComp<LineConvertTransformComp>(compName, compData);
	AddAndLoadComp<EyeComp>(compName, compData);
	AddAndLoadComp<EyeStateComp>(compName, compData);
	AddAndLoadComp<EaseingComp>(compName, compData);
	AddAndLoadComp<CountComp>(compName, compData);
	AddAndLoadComp<Direction2DComp>(compName, compData);
	AddAndLoadComp<EatCloudComp>(compName, compData);
	AddAndLoadComp<RemoveCloudComp>(compName, compData);
	AddAndLoadComp<Mass2DComp>(compName, compData);
	AddAndLoadComp<JumpComp>(compName, compData);
	AddAndLoadComp<Aabb2DComp>(compName, compData);
	AddAndLoadComp<CollectionComp>(compName, compData);
	AddAndLoadComp<FollowCamera2DComp>(compName, compData);
	AddAndLoadComp<GoalComp>(compName, compData);
	AddAndLoadComp<InvisibleComp>(compName, compData);
	AddAndLoadComp<KeyComp>(compName, compData);
	AddAndLoadComp<TextureHandlesComp>(compName, compData);
	AddAndLoadComp<InstanceTimeComp>(compName, compData);
	AddAndLoadComp<UIDrawComp>(compName, compData);
	AddAndLoadComp<UITransformComp>(compName, compData);
	AddAndLoadComp<BackGroundComp>(compName, compData);
	AddAndLoadComp<UvOperatorComp>(compName, compData);
	AddAndLoadComp<TitleInputComp>(compName, compData);
	AddAndLoadComp<StageSelectInputComp>(compName, compData);
	AddAndLoadComp<EatCloudAnimationComp>(compName, compData);
	AddAndLoadComp<ResultInputComp>(compName, compData);
	AddAndLoadComp<UvOperatorComp>(compName, compData);
	AddAndLoadComp<NumSpriteComp>(compName, compData);
	AddAndLoadComp<EasingSpriteComp>(compName, compData);
	AddAndLoadComp<ArrowComp>(compName, compData);
	AddAndLoadComp<CloudUIComp>(compName, compData);
	AddAndLoadComp<SpriteUVChangeComp>(compName, compData);
}

