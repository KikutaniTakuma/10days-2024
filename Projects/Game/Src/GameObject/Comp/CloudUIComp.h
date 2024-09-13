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

	std::vector<Lamb::SafePtr<class UIDrawComp>> cloudsUI_;
	Lamb::SafePtr<class ChildrenObjectComp> childrenComp_;
	Lamb::SafePtr<class SpriteRenderDataComp> spriteRenderDataComp_;
	Lamb::SafePtr<class UIDrawComp> UIDraw_;

};

