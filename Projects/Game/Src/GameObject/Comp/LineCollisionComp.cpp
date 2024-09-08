#include "LineCollisionComp.h"
#include "LineRenderDataComp.h"

void LineCollisionComp::Init()
{
	lineComp_ = object_.AddComp<LineComp>();
	transFormComp_ = object_.AddComp<TransformComp>();
}

void LineCollisionComp::FirstUpdate()
{
	if (object_.HasComp<ObbComp>()) {
		Lamb::SafePtr transformComp = object_.GetComp<TransformComp>();

		transformComp->translate = Vector3::Lerp(lineComp_->start, lineComp_->end, 0.5f);
		transformComp->scale = { (lineComp_->start - lineComp_->end).Length(), 10.0f, 10.0f };

		Vector3 to = (lineComp_->end - lineComp_->start).Normalize();
#ifdef _DEBUG
		transformComp->eulerRotate = Quaternion::DirectionToDirection(Vector3::kXIdentity, to).ToEuler();
#else
		transformComp->rotate = Quaternion::DirectionToDirection(Vector3::kXIdentity, to);
#endif // _DEBUG
	}

	// 初期化
	mostNearCollisionObjectPtr_ = nullptr;
}

bool LineCollisionComp::IsCollisionHasTag(ObbComp* obbComp)
{
	bool hasTag = false;
	for (auto& i : collisionTags_) {
		if (obbComp->getObject().HasTag(i)) {
			currentCollisionTag_ = i;
			hasTag = true;
			break;
		}
	}

	// タグをもっていなかったら当たり判定をしない
	if (not hasTag) {
		return false;
	}

	// 毎フレームリセットする
	if (not isCollision_.OnEnter()) {
		isCollision_ = false;
#ifdef _DEBUG
		color_ = 0xffffffff;
#endif // _DEBUG
	}

	// 当たり判定
	bool isCollision = obbComp->IsCollision(lineComp_->start, lineComp_->end);

	if (isCollision) {
		// 当たり判定フラグ追加
		isCollision_ = true;
		
		// もっとも近いオブジェクトのポインタを保存
		// emptyだった場合はそのまま保存
		if (mostNearCollisionObjectPtr_.empty()) {
			mostNearCollisionObjectPtr_ = &(obbComp->getObject());
		}
		else {
			float32_t preMostNearObjectLength = (mostNearCollisionObjectPtr_->GetComp<TransformComp>()->translate - lineComp_->start).Length();
			float32_t currentMostNearObjectLength = (obbComp->GetTransformComp().translate - lineComp_->start).Length();
			// いま持っているオブジェクトより近かったらポインタを代入
			if (currentMostNearObjectLength < preMostNearObjectLength) {
				mostNearCollisionObjectPtr_ = &(obbComp->getObject());
			}
		}

		// 当たってたら色変更
#ifdef _DEBUG
		color_ = 0xff0000ff;
#endif // _DEBUG
	}

	return isCollision;
}

void LineCollisionComp::Save(nlohmann::json& json) {
	SaveCompName(json);
	json["CollisionTag"] = nlohmann::json::array();
	for (auto& i : collisionTags_) {
		json["CollisionTags"].push_back(i);
	}
}

void LineCollisionComp::Load([[maybe_unused]]nlohmann::json& json) {
	for (auto& i : json["CollisionTags"]) {
		collisionTags_.insert(i);
	}
}

void LineCollisionComp::Debug([[maybe_unused]] const std::string& guiName) {
#ifdef _DEBUG
	if (ImGui::TreeNode(guiName.c_str())) {

		ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(250, 100), ImGuiWindowFlags_NoTitleBar);
		for (auto& i : collisionTags_) {
			if (ImGui::Button("erase")) {
				collisionTags_.erase(i);
				break;
			}
			ImGui::SameLine();
			ImGui::Text("tag : % s", i.c_str());
		}
		ImGui::EndChild();

		inputTag_.resize(32);
		ImGui::Text("current collision tag : %s", currentCollisionTag_.c_str());
		ImGui::InputText(
			"タグ",
			inputTag_.data(),
			inputTag_.size()
		);
		if (ImGui::Button("タグ追加")) {
			std::string addtag;
			for (auto& i : inputTag_) {
				if (i == '\0') {
					break;
				}
				addtag.push_back(i);
			}
			collisionTags_.insert(addtag);
		}
		ImGui::TreePop();
}
#endif // _DEBUG

}

const LineComp& LineCollisionComp::GetLineComp() const
{
	return *lineComp_;
}

const Lamb::SafePtr<const Object>& LineCollisionComp::GetMostNearCollisionObjectPtr() const
{
	return mostNearCollisionObjectPtr_;
}
