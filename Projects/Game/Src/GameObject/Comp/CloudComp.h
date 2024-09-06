#pragma once
 #include "../Object.h"

 class CloudComp : public IComp {
 public:

	 using IComp::IComp;

	 ~CloudComp() = default;

 public:

	 void Init() override;
	 
	 void Update() override;

	 void Save(nlohmann::json& json) override;
	 void Load(nlohmann::json& json) override;

 private:

	 float32_t cloudSize_ = 32.0f;

	 Lamb::SafePtr<class TransformComp> transformComp_;

	 Lamb::SafePtr<class SpriteRenderComp> spriteRenderComp_;

	 Lamb::SafePtr<class ObbPushComp> collision_;

	 Lamb::SafePtr<class FlagComp> flagComp_;

 };