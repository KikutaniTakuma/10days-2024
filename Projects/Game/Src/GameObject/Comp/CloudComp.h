#pragma once
 #include "../Object.h"
#include "Aabb2DComp.h"

 class CloudComp : public IComp {
 public:

	 using IComp::IComp;

	 ~CloudComp() = default;

	 static constexpr float kCloudSize_ = 32.0f;

 public:

	 void Init() override;
	 
	 void Update() override;

	 void Finalize() override;

	 const Lamb::Flg& GetIsActive() const;

	 void SetIsActive(bool flag);

	 void SetPosition(const Vector3& position);

	 int32_t GetMassX() const;
	 int32_t GetMassY() const;

	 void Save(nlohmann::json& json) override;
	 void Load(nlohmann::json& json) override;

	 /*ObbPushComp& GetObbPushComp();
	 const ObbPushComp& GetObbPushComp() const;*/

	 Aabb2DComp& GetAabb2DComp();
	 const Aabb2DComp& GetAabb2DComp() const;

 private:

	 Lamb::SafePtr<class TransformComp> transformComp_;

	 Lamb::SafePtr<class SpriteRenderComp> spriteRenderComp_;

	 Lamb::SafePtr<class SpriteRenderDataComp> spriteRenderDataComp_;

	 /*Lamb::SafePtr<class ObbPushComp> collision_;*/

	 Lamb::SafePtr<class FlagComp> flagComp_;

	 Lamb::SafePtr<class Mass2DComp> mass_;

	 Lamb::SafePtr<class Aabb2DComp> aabbCollision_;

 };