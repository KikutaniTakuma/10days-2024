#include "Aabb2DComp.h"
#include "TransformComp.h"
#include "../Manager/Aabb2DManager.h"

void Aabb2DComp::Init()
{
	/*Aabb2DManager::GetInstance()->Set(this);*/
	transformComp_ = object_.AddComp<TransformComp>();
	positions_ = std::make_unique<std::array<Vector3, 4>>();
	prePositions_ = std::make_unique<std::array<Vector3, 4>>();
}

void Aabb2DComp::Finalize()
{
	/*Aabb2DManager::GetInstance()->Erase(this);*/
}

void Aabb2DComp::FirstUpdate()
{
	UpdatePosAndOrient();
}

void Aabb2DComp::Event()
{
	UpdatePosAndOrient();
}

void Aabb2DComp::LastUpdate()
{
	for (size_t i = 0; i < static_cast<size_t>(Point::kNum); i++) {
		prePositions_->at(i) = positions_->at(i);
	}
}

void Aabb2DComp::UpdatePosAndOrient()
{

	const Mat4x4& worldMatrix = transformComp_->GetWorldMatrix();

	min_ = (Vector3{ -0.5f,-0.5f,-0.5f }) * Mat4x4::MakeAffin(scale_, Vector3(), Vector3()) * worldMatrix;

	max_ = (Vector3{ +0.5f,+0.5f,+0.5f }) * Mat4x4::MakeAffin(scale_, Vector3(), Vector3()) * worldMatrix;

	//左上
	positions_->at(static_cast<size_t>(Point::kLeftUp)) = Vector3{ min_.x, max_.y, (min_.z + max_.z) * 0.5f  };
	//右上
	positions_->at(static_cast<size_t>(Point::kRightUp)) = Vector3{ max_.x - 0.0f, max_.y, (min_.z + max_.z) * 0.5f };
	//左下
	positions_->at(static_cast<size_t>(Point::kLeftUnder)) = Vector3{ min_.x, min_.y + 0.0f, (min_.z + max_.z) * 0.5f };
	//右下
	positions_->at(static_cast<size_t>(Point::kRightUnder)) = Vector3{ max_.x - 0.0f, min_.y + 0.0f, (min_.z + max_.z) * 0.5f };

}

void Aabb2DComp::UpdatePrePosition()
{
	for (size_t i = 0; i < static_cast<size_t>(Point::kNum); i++) {
		prePositions_->at(i) = positions_->at(i);
	}
}

bool Aabb2DComp::IsCollision(Aabb2DComp* const other)
{

	if ((min_.x <= other->max_.x and max_.x >= other->min_.x) and
		(min_.y <= other->max_.y and max_.y >= other->min_.y)) {
		return true;
	}

	return false;

}

bool Aabb2DComp::IsCollisionPoint(const Vector3& point)
{

	if (min_.x <= point.x and max_.x >= point.x and
		min_.y <= point.y and max_.y >= point.y) {
		return true;
	}

	return false;
}

bool Aabb2DComp::CollisionHasTag(Aabb2DComp* const other)
{

	bool hasTag = false;
	for (auto& i : collisionTags_) {
		if (other->getObject().HasTag(i)) {
			hasTag = true;
			break;
		}
	}

	if (hasTag) {
		return IsCollision(other);
	}

	return false;
}

void Aabb2DComp::Save(nlohmann::json& json) {
	SaveCompName(json);
	json["collsiionTags"] = nlohmann::json::array();
	for (auto& i : collisionTags_) {
		json["collsiionTags"].push_back(i);
	}
	json["scale"] = nlohmann::json::array({ scale_.x, scale_.y, scale_.z });
}

void Aabb2DComp::Load([[maybe_unused]] nlohmann::json& json) {
	collisionTags_.clear();
	collisionTags_.reserve(json["collsiionTags"].size());
	for (size_t i = 0; i < json["collsiionTags"].size(); i++) {
		collisionTags_.insert(json["collsiionTags"][i].get<std::string>());
	}

	for (size_t i = 0; i < json["scale"].size(); i++) {
		scale_[i] = json["scale"][i].get<float32_t>();
	}

}

