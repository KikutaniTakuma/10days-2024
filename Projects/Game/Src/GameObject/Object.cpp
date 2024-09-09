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
#include "Comp/TransformComp.h"
#include "Comp/CloudComp.h"
#include "Comp/FlagComp.h"
#include "Comp/PlayerComp.h"
#include "Comp/CountComp.h"
#include "Comp/Direction2DComp.h"
#include "Comp/EatCloudComp.h"
#include "Comp/RemoveCloudComp.h"
#include "Comp/Mass2DComp.h"
#include "Comp/JumpComp.h"

#include "Comp/LineComp.h"
#include "Comp/LineRenderComp.h"
#include "Comp/LineRenderDataComp.h"
#include "Comp/LineCollisionComp.h"

#include "Comp/EyeComp.h"
#include "Comp/EyeStateComp.h"
#include "Comp/EaseingComp.h"

void Object::Init() {
	/*for (auto& i : components_) {
		i.second->Init();
	}*/
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
			ImGui::Text("%s, ", i.c_str());
		}
		ImGui::EndChild();
		if (ImGui::TreeNode("componets")) {
			for (auto& i : components_) {
				i.second->Debug(i.first);
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
		DebugAdd<TransformComp>();
		DebugAdd<FlagComp>();
		DebugAdd<CloudComp>();
		DebugAdd<PlayerComp>();
		DebugAdd<CountComp>();
		DebugAdd<Direction2DComp>();
		DebugAdd<EatCloudComp>();
		DebugAdd<RemoveCloudComp>();
		DebugAdd<Mass2DComp>();
		DebugAdd<JumpComp>();
		DebugAdd<LineComp>();
		DebugAdd<LineRenderComp>();
		DebugAdd<LineRenderDataComp>();
		DebugAdd<LineCollisionComp>();
		DebugAdd<EyeComp>();
		DebugAdd<EyeStateComp>();
		DebugAdd<EaseingComp>();
		
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
	AddAndLoadComp<TransformComp>(compName, compData);
	AddAndLoadComp<FlagComp>(compName, compData);
	AddAndLoadComp<CloudComp>(compName, compData);
	AddAndLoadComp<PlayerComp>(compName, compData);
	AddAndLoadComp<LineComp>(compName, compData);
	AddAndLoadComp<LineRenderComp>(compName, compData);
	AddAndLoadComp<LineRenderDataComp>(compName, compData);
	AddAndLoadComp<LineCollisionComp>(compName, compData);
	AddAndLoadComp<EyeComp>(compName, compData);
	AddAndLoadComp<EyeStateComp>(compName, compData);
	AddAndLoadComp<EaseingComp>(compName, compData);
	AddAndLoadComp<CountComp>(compName, compData);
	AddAndLoadComp<Direction2DComp>(compName, compData);
	AddAndLoadComp<EatCloudComp>(compName, compData);
	AddAndLoadComp<RemoveCloudComp>(compName, compData);
	AddAndLoadComp<Mass2DComp>(compName, compData);
	AddAndLoadComp<JumpComp>(compName, compData);
}

