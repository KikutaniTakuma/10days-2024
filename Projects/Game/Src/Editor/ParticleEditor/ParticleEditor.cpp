#include "ParticleEditor.h"
#include <cassert>
#include "imgui.h"
#include "Utils/FileUtils.h"

ParticleEditor* ParticleEditor::instance_ = nullptr;

void ParticleEditor::Initialize() {
	assert(!instance_);
	instance_ = new ParticleEditor;
	instance_->camera_.pos.z = -5.0f;
	instance_->camera_.Update();
}

void ParticleEditor::Finalize() {
	delete instance_;
	instance_ = nullptr;
}

ParticleEditor* ParticleEditor::GetInstance() {
	return instance_;
}

void ParticleEditor::Editor() {
#ifdef _DEBUG
	if (!isOpen_) {
		inputLoadString_.resize(128);
		ImGui::Begin("ParticleEditor");
		if (ImGui::TreeNode("load")) {
			inputLoadString_.resize(128);
			ImGui::InputText("load name", inputLoadString_.data(), inputLoadString_.size());
			if (ImGui::Button("Create") && !inputLoadString_.empty()) {
				std::string createString;
				createString.clear();
				for (const auto& i : inputLoadString_) {
					if (i == '\0') {
						break;
					}
					createString.push_back(i);
				}
				particle_.LoadSettingDirectory(createString);
				currentLoadString_ = createString;
				isOpen_ = true;
			}
			ImGui::TreePop();
		}
		ImGui::End();
	}
	else {
		ImGui::Begin("ParticleEditor");
		ImGui::Checkbox("is3DCamera", &is3DCamera_);
		ImGui::Checkbox("isLocalCamera", &isLocalCamera_);

		ImGui::End();
		particle_.Debug(currentLoadString_);
		if (particle_.GetIsClose()) {
			isOpen_ = false;
		}
		particle_.Update();
	}

#endif // _DEBUG
}

void ParticleEditor::Draw([[maybe_unused]] const Mat4x4& camera) {
#ifdef _DEBUG
	if (isOpen_) {
		particle_.Draw(Vector3::kZero, camera);
	}
#endif // _DEBUG
}