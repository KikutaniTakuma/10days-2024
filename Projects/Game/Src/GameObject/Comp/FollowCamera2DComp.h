#pragma once
#include "../Object.h"

class FollowCamera2DComp : public IComp {
public:

	using IComp::IComp;

	~FollowCamera2DComp() = default;

	void Init() override;

	void Move() override;

	void SetPlayerComp(class PlayerComp* playerComp);

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	Lamb::SafePtr<class Camera2DComp> camera_;

	Lamb::SafePtr<class TransformComp> transform_;

	Lamb::SafePtr<class PlayerComp> target_;
	Lamb::SafePtr<class TransformComp> targetTransform_;

	Vector2 min_{ 368.0f,0.0f };
	Vector2 max_{ 3472.0f, 0.0f };

};
