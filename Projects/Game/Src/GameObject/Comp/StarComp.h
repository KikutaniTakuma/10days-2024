#pragma once
#include "../Object.h"

class StarComp : public IComp {
public:

	using IComp::IComp;

	~StarComp() = default;

	void Init() override;

	void Update() override;

	void Start();

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	bool isEasingStart_ = false;

	bool isEasingEnd_ = false;

private:

	Lamb::SafePtr <class UIDrawComp> UIDraw_;

	Lamb::SafePtr <class UITransformComp> UITransform_;

	Lamb::SafePtr<class UISpriteRenderDataComp> spriteRenderDataComp_;

	Lamb::SafePtr<class EaseingComp> easing_;

	Vector3 startScale_ = { 0.0f,0.0f,0.0f };
	Vector3 endScale_ = { 48.0f,48.0f,48.0f };

};

