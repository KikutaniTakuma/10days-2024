#pragma once
#include "../Object.h"
#include <vector>

class CloudUIComp : public IComp {
public:

	using IComp::IComp;

	void Init() override;

	void Load() override;

	void Update() override;

	~CloudUIComp() = default;

	void SetCountComp(class CountComp* countComp);

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	//プレイヤーの雲カウント
	Lamb::SafePtr <class CountComp> count_;

private:

	std::vector<Lamb::SafePtr<class SpriteUVChangeComp>> cloudsUI_;
	Lamb::SafePtr<class ChildrenObjectComp> childrenComp_;
	Lamb::SafePtr<class UISpriteRenderDataComp> spriteRenderDataComp_;
	Lamb::SafePtr<class UIDrawComp> UIDraw_;
	Lamb::SafePtr<class UITransformComp> UItransform_;


	// 胃の画像
	uint32_t parentUITexID_ = 0;
	// 通常
	uint32_t cloudTexID_ = 0;
	// 点線のほう
	uint32_t cloudOutlineLineTexID_ = 0;
};

