#pragma once
#include "../Object.h"
#include "EatCloudAnimationComp.h"

class EatAnimationControllComp : public IComp {
public:
	using IComp::IComp;

	~EatAnimationControllComp() = default;

public:
	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;
	void Load() override;

public:
	void Init();

	void SetIsLeft(bool isLeft);

	// アニメーション開始
	void StartAnimation();

private:
	std::vector<Lamb::SafePtr<EatCloudAnimationComp>> eatCloudAnimationComps_;
	Lamb::SafePtr<class ChildrenObjectComp> childrenComp_;
};
