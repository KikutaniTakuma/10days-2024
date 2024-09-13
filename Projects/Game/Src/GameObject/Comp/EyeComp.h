#pragma once
#include "../Object.h"
#include "Drawers/Particle/Particle.h"
#include "Engine/Graphics/Tex2DAniamtor/Tex2DAniamtor.h"

class EyeComp : public IComp {
public:
	using IComp::IComp;

	~EyeComp() = default;

public:
	void Init() override;

	void SetPlayerComp(class PlayerComp* playerComp);
	void SetBeamTransformComp();

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	void FirstUpdate() override;
	// 当たり判定後の処理
	void Event() override;

	void Update() override;

	void LastUpdate() override;

	void Draw(CameraComp* cameraComp) override;

	// 攻撃してるとき
	bool IsFire() const;

	// 狙っているとき
	bool IsAiming() const;

	// 狙いを定めたとき
	bool IsAimFixed() const;


	Lamb::SafePtr<class PlayerComp> GetPlayerComp() {
		return playerComp_;
	}

private:
	// これは別のオブジェクトが持っているPlayerComp
	Lamb::SafePtr<class PlayerComp> playerComp_;
	// プレイヤーのTransformComp
	Lamb::SafePtr<class TransformComp> playerTransformComp_;
	Lamb::SafePtr<class ObbComp> playerObbComp_;

private:
	Lamb::SafePtr<class TransformComp> transformComp_;
	Lamb::SafePtr<class SpriteRenderDataComp> renderDataComp_;

	// 黒目の子オブジェクト(これはベータ版で使う)
	Lamb::SafePtr<class ChildrenObjectComp> childrenObjectComp_;
	Lamb::SafePtr<class LineComp> childrenBeamLineComp_;
	Lamb::SafePtr<class TransformComp> childrenTransformComp_;
	Lamb::SafePtr<class SpriteRenderDataComp> childrenBeamRenderDataComp_;

	Lamb::SafePtr<class LineComp> beamLineComp_;
	Lamb::SafePtr<class LineCollisionComp> beamLineCollisionComp_;
	Lamb::SafePtr<class LineRenderDataComp> beamLineRenderDataComp_;

	Lamb::SafePtr<class EyeStateComp> eyeStateComp_;

	Lamb::SafePtr<class EaseingComp> easeingComp_;

	Vector3 aimDirection_;
	Vector3 aimPoint_;
	
	//雲を一個消したかどうか
	bool isDeleteCloud_ = false;

	bool isEasesingStart_ = false;
	float32_t easeingStartPosX = 0.0f;

	// パーティクル
	std::unique_ptr<Particle> paritcle_;

	uint32_t animtionTExtureHandle_ = 0;
	Tex2DAniamtor animator_;
};
