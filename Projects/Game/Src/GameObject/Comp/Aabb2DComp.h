#pragma once
#include "../Object.h"

class Aabb2DComp : public IComp {
public:

	enum class Point {
		kLeftUp,
		kRightUp,
		kLeftUnder,
		kRightUnder,

		//最大数
		kNum
	};

	using IComp::IComp;

	void Init() override;

	void Finalize() override;

	void FirstUpdate() override;

	void Event() override;

	void LastUpdate() override;

	/// <summary>
	/// 移動したら呼び出すこと
	/// </summary>
	void UpdatePosAndOrient();

	void UpdatePrePosition();

	bool IsCollision(Aabb2DComp* const other);
	bool IsCollisionPoint(const Vector3& point);

	bool CollisionHasTag(Aabb2DComp* const other);

	~Aabb2DComp() = default;

	const Lamb::Flg& GetIsCollision() const {
		return isCollision_;
	}

	const Vector3& GetPosition(Point point) const {
		return positions_->at(static_cast<size_t>(point));
	}

	const Vector3& GetPrePosition(Point point) const {
		return prePositions_->at(static_cast<size_t>(point));
	}

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	Vector3 scale_{ 1.0f,1.0f,1.0f };

private:

	Lamb::SafePtr<class TransformComp> transformComp_;

	std::unique_ptr<std::array<Vector3, 4>> positions_;

	std::unique_ptr<std::array<Vector3, 4>> prePositions_;

	Vector3 min_{};

	Vector3 max_{};

	std::unordered_set<std::string> collisionTags_;

	Lamb::Flg isCollision_;

};
