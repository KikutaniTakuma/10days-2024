#pragma once
#include "../Object.h"

class BackGroundComp : public IComp {
public:

	using IComp::IComp;

	~BackGroundComp() = default;

	void Init() override;

	void Move() override;

	void SetFollowCameraComp(class FollowCamera2DComp* followCameraComp);

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	Lamb::SafePtr<class TransformComp> transform_;

	Lamb::SafePtr<class SpriteRenderComp> spriteRenderComp_;

	Lamb::SafePtr<class FollowCamera2DComp> target_;

	Lamb::SafePtr<class TransformComp> targetTransform_;

};
