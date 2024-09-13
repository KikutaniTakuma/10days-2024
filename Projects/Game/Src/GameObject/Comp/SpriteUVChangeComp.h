#pragma once
#include "../Object.h"
class SpriteUVChangeComp : public IComp {
public:
	using IComp::IComp;

	~SpriteUVChangeComp() = default;

public:
	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	void Init() override;

	void LastUpdate() override;

	Lamb::SafePtr<class UISpriteRenderDataComp> GetSpriteRenderDataComp() const {
		return spriteRenderDataComp_;
	}

	Lamb::SafePtr<class UITransformComp> GetUITransformComp() const {
		return uiTransformCompComp_;
	}

	void EnableFlag();
	void UnenableFlag();

public:
	Lamb::SafePtr<class FlagComp> flagComp_;
	Lamb::SafePtr<class UISpriteRenderDataComp> spriteRenderDataComp_;
	Lamb::SafePtr<class UITransformComp> uiTransformCompComp_;
};
