#include "ChildrenObjectComp.h"
#include "TransformComp.h"
#include "UITransformComp.h"

void ChildrenObjectComp::Finalize() {
	objects_.clear();
}

void ChildrenObjectComp::AddObject(Lamb::SafePtr<Object> object) {
	// nullなら早期リターン
	if (object.empty()) {
		return;
	}
	auto itr = std::find_if(objects_.begin(), objects_.end(),
		[&object](const std::unique_ptr<Object>& element)->bool {
			return object.get() == element.get();
		}
	);

	// なかったら追加
	if (itr == objects_.end()) {
		objects_.insert(std::unique_ptr<Object>(object.get()));
		Lamb::SafePtr<UITransformComp> transformUI;
		if (object_.HasComp<UITransformComp>()) {
			transformUI = object_.GetComp<UITransformComp>();
		}
		Lamb::SafePtr<TransformComp> transform;
		if (object_.HasComp<TransformComp>()) {
			transform = object_.GetComp<TransformComp>();
		}

		// トランスフォームコンポーネントを持っていたら親子関係を結ぶ
		if (object->HasComp<TransformComp>() and transform.have()) {
			object->GetComp<TransformComp>()->SetParent(transform);
		}
		// トランスフォームコンポーネントを持っていたら親子関係を結ぶ
		if (object->HasComp<UITransformComp>()  and transformUI.have()) {
			object->GetComp<UITransformComp>()->SetParent(transformUI);
		}
	}
}

void ChildrenObjectComp::EraseObject(Object* object) {
	auto itr = std::find_if(objects_.begin(), objects_.end(), 
		[&object](const std::unique_ptr<Object>& element)->bool {
			return object == element.get();
		}
	);
	// あったら削除
	if (itr != objects_.end()) {
		objects_.erase(itr);
	}
}

void ChildrenObjectComp::Clear() {
	objects_.clear();
}

void ChildrenObjectComp::ClearObjects() {
	objects_.clear();
}

void ChildrenObjectComp::FirstUpdate() {
	for (auto& i : objects_) {
		i->FirstUpdate();
	}
}

void ChildrenObjectComp::Move() {
	for (auto& i : objects_) {
		i->Move();
	}
}

void ChildrenObjectComp::Event() {
	for (auto& i : objects_) {
		i->Event();
	}
}

void ChildrenObjectComp::Update() {
	for (auto& i : objects_) {
		i->Update();
	}
}

void ChildrenObjectComp::LastUpdate() {
	for (auto& i : objects_) {
		i->LastUpdate();
	}
}

void ChildrenObjectComp::Draw(CameraComp* cameraComp) {
	for (auto& i : objects_) {
		i->Draw(cameraComp);
	}
}

void ChildrenObjectComp::Draw()
{
	for (auto& i : objects_) {
		i->Draw();
	}
}

void ChildrenObjectComp::Debug([[maybe_unused]]const std::string& guiName) {
#ifdef _DEBUG
	if (ImGui::TreeNode(guiName.c_str())) {
		size_t objectCount = 0;
		if (ImGui::Button("Add objetct")) {
			AddObject(Lamb::MakeSafePtr<Object>());
			ImGui::TreePop();
			return;
		}

		for (auto itr = objects_.begin(); itr != objects_.end(); itr++) {
			if (ImGui::Button("erase")) {
				objects_.erase(itr);
				break;
			}
			ImGui::SameLine();
			(*itr)->Debug("object_" + std::to_string(objectCount));

			Lamb::SafePtr<UITransformComp> transformUI;
			if (object_.HasComp<UITransformComp>()) {
				transformUI = object_.GetComp<UITransformComp>();
			}
			Lamb::SafePtr<TransformComp> transform;
			if (object_.HasComp<TransformComp>()) {
				transform = object_.GetComp<TransformComp>();
			}

			// トランスフォームコンポーネントを持っていたら親子関係を結ぶ
			if ((*itr)->HasComp<TransformComp>() and transform.have()) {
				(*itr)->GetComp<TransformComp>()->SetParent(transform);
			}
			// トランスフォームコンポーネントを持っていたら親子関係を結ぶ
			if ((*itr)->HasComp<UITransformComp>() and transformUI.have()) {
				(*itr)->GetComp<UITransformComp>()->SetParent(transformUI);
			}

			objectCount++;
		}



		ImGui::TreePop();
	}
#endif // _DEBUG
}

void ChildrenObjectComp::Save(nlohmann::json& json) {
	SaveCompName(json);

	json["Children"] = nlohmann::json::array();

	for (auto& i : objects_) {
		json["Children"].push_back(nlohmann::json::object());
		i->Save(json["Children"].back());
	}
}

void ChildrenObjectComp::Load(nlohmann::json& json) {
	objects_.clear();
	auto& childrenJson = json["Children"];
	for (size_t i = 0; i < childrenJson.size(); i++) {
		if (childrenJson[i]["type"].get<std::string>() == "Object") {
			auto newObject = Lamb::MakeSafePtr<Object>();
			newObject->Load(childrenJson[i]["Comps"]);
			AddObject(newObject);
		}
	}
}

void ChildrenObjectComp::Load()
{
	for (auto itr = objects_.begin(); itr != objects_.end(); itr++) {
		Lamb::SafePtr<UITransformComp> transformUI;
		if (object_.HasComp<UITransformComp>()) {
			transformUI = object_.GetComp<UITransformComp>();
		}
		Lamb::SafePtr<TransformComp> transform;
		if (object_.HasComp<TransformComp>()) {
			transform = object_.GetComp<TransformComp>();
		}

		// トランスフォームコンポーネントを持っていたら親子関係を結ぶ
		if ((*itr)->HasComp<TransformComp>() and transform.have()) {
			(*itr)->GetComp<TransformComp>()->SetParent(transform);
		}
		// トランスフォームコンポーネントを持っていたら親子関係を結ぶ
		if ((*itr)->HasComp<UITransformComp>() and transformUI.have()) {
			(*itr)->GetComp<UITransformComp>()->SetParent(transformUI);
		}
	}
}

const std::unordered_set<std::unique_ptr<Object>>& ChildrenObjectComp::GetObjects() const
{
	return objects_;
}

