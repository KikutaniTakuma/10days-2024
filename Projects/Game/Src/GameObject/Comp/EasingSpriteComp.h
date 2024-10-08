#pragma once
#include "../Object.h"

class EasingSpriteComp : public IComp {
public:

	using IComp::IComp;

	~EasingSpriteComp() = default;

	void Init() override;

	void Move() override;

	void Debug(const std::string& guiName) override;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	Lamb::SafePtr<class UISpriteRenderDataComp> spriteRenderDataComp_;

	Lamb::SafePtr<class UIDrawComp> uiDraw_;

	Lamb::SafePtr<class EaseingComp> easing_;

	Lamb::SafePtr<class UITransformComp> transform_;

	Vector3 translateStart_ = { 0.0f,0.0f,0.0f };
	Vector3 translateEnd_ = { 0.0f,0.0f,0.0f };

	Vector3 scaleStart_ = { 0.0f,0.0f,0.0f };
	Vector3 scaleEnd_ = { 0.0f,0.0f,0.0f };

	float transparStart_ = 1.0f;
	float transparEnd_ = 1.0f;


};
