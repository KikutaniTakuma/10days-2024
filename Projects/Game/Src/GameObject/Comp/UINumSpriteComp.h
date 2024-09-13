#pragma once
#include "../Object.h"

class UINumSpriteComp : public IComp {
public:

	using IComp::IComp;

	~UINumSpriteComp() = default;

	void Init() override;

	void Event() override;

	void Debug(const std::string& guiName) override;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	void SetIsUpdate(bool flag) { isUpdate_ = flag; }

	int32_t divide_ = 1;

	bool isUpdate_ = true;

private:

	Lamb::SafePtr<class UISpriteRenderDataComp> spriteRenderDataComp_;

	Lamb::SafePtr<class UITransformComp> transform_;

	Lamb::SafePtr<class UIDrawComp> UIDraw_;

	int32_t preStageNum_ = 1;

	int32_t offset_ = 0;

	int32_t preOffset_ = 0;

	float smaleScale_ = 108.0f;

	float defaultScale_ = 128.0f;

	float addValue_ = 1.0f;

};
