#pragma once
#include "../Object.h"

class NumSpriteComp : public IComp {
public:

	using IComp::IComp;

	~NumSpriteComp() = default;

	void Init() override;

	void Event() override;

	void Debug(const std::string& guiName) override;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	void SetIsUpdate(bool flag) { isUpdate_ = flag; }

private:

	Lamb::SafePtr<class SpriteRenderDataComp> spriteRenderDataComp_;

	Lamb::SafePtr<class TransformComp> transform_;

	Lamb::SafePtr<class SpriteRenderComp> spriteRenderComp_;

	int32_t divide_ = 1;

	int32_t preStageNum_ = 1;

	int32_t offset_ = 0;

	int32_t preOffset_ = 0;

	float smaleScale_ = 108.0f;

	float defaultScale_ = 128.0f;

	float addValue_ = 1.0f;

	bool isUpdate_ = true;

};
