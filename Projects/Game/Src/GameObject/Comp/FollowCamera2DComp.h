#pragma once
#include "../Object.h"

class FollowCamera2DComp : public IComp {
public:

	using IComp::IComp;

	~FollowCamera2DComp() = default;

	void Init() override;

	void Move() override;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	Lamb::SafePtr<class Camera2DComp> camera_;

	Lamb::SafePtr<class TransformComp> transform_;

};
