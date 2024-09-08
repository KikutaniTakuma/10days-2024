#pragma once
#include "../Object.h"
class EyeComp : public IComp {
public:
	using IComp::IComp;

	~EyeComp() = default;

public:
	void Init() override;

	void SetPlayerComp(class PlayerComp* playerComp);

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	void FirstUpdate() override;
	// 当たり判定後の処理
	void Event() override;


private:
	// これは別のオブジェクトが持っているPlayerComp
	Lamb::SafePtr<class PlayerComp> playerComp_;
	// プレイヤーのTransformComp
	Lamb::SafePtr<class TransformComp> playerTransformComp_;
	Lamb::SafePtr<class ObbComp> playerObbComp_;

private:
	Lamb::SafePtr<class TransformComp> transformComp_;

	// 黒目の子オブジェクト(これはベータ版で使う)
	Lamb::SafePtr<class ChildrenComp> eyeBlackEye_;

	Lamb::SafePtr<class LineComp> beamLineComp_;
	Lamb::SafePtr<class LineCollisionComp> beamLineCollisionComp_;

	Lamb::SafePtr<class EyeStateComp> eyeStateComp_;
};
