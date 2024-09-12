#pragma once
#include "../Object.h"

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

	// 攻撃してるとき
	bool IsFire() const;

	// 狙っているとき
	bool IsAiming() const;

	// 狙いを定めたとき
	bool IsAimFixed() const;

private:
	// これは別のオブジェクトが持っているPlayerComp
	Lamb::SafePtr<class PlayerComp> playerComp_;
	// プレイヤーのTransformComp
	Lamb::SafePtr<class TransformComp> playerTransformComp_;
	Lamb::SafePtr<class ObbComp> playerObbComp_;

private:
	Lamb::SafePtr<class TransformComp> transformComp_;

	// 黒目の子オブジェクト(これはベータ版で使う)
	Lamb::SafePtr<class ChildrenObjectComp> childrenObjectComp_;
	Lamb::SafePtr<class LineComp> childrenBeamLineComp_;
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
};
