#pragma once
#include "../Object.h"

class PlayerComp : public IComp {
public:

	using IComp::IComp;

	~PlayerComp() = default;

public:

	void Init() override;

	void FirstUpdate() override;

	void Move() override;

	void Event() override;

	void Update() override;

	void LastUpdate() override;

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	void SetIsBeamCollision(const Lamb::Flg& collisionFlg);

private:

	Lamb::SafePtr<class TransformComp> transform_;

	Lamb::SafePtr<class SpriteRenderComp> sprite_;

	Lamb::SafePtr <class InputMoveComp> move_;

	Lamb::SafePtr<class FallComp> fall_;

	Lamb::SafePtr<class ObbPushComp> collision_;

	Lamb::SafePtr <class FlagComp> isDead_;


#pragma region 菊谷が追加 2024/9/8
	Lamb::Flg& beamCollisionFlg_;
#pragma endregion

};