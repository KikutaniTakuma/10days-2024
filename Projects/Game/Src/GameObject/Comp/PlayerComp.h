#pragma once
#include "../Object.h"

class PlayerComp : public IComp {
public:

	using IComp::IComp;

	~PlayerComp() = default;

	static constexpr float kPlayerSize_ = 24.0f;

	static constexpr float kPlayerHalfSize_ = 12.0f;

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

	void CheckCollision();

private:

	Lamb::SafePtr<class TransformComp> transform_;

	Lamb::SafePtr<class SpriteRenderComp> sprite_;

	Lamb::SafePtr<class SpriteRenderDataComp> spriteRenderData_;

	Lamb::SafePtr <class InputMoveComp> move_;

	Lamb::SafePtr<class FallComp> fall_;

	Lamb::SafePtr<class ObbPushComp> collision_;

	Lamb::SafePtr <class FlagComp> isDead_;

	Lamb::SafePtr<class Direction2DComp> direction_;

	Lamb::SafePtr<class CsvDataComp> csvData_;

	Lamb::SafePtr<class EatCloudComp> eatCloud_;

	Lamb::SafePtr<class RemoveCloudComp> removeCloud_;

	Lamb::SafePtr<class CountComp> count_;

	Lamb::SafePtr<class Mass2DComp> mass_;

	Lamb::SafePtr<class JumpComp> jump_;

	Lamb::SafePtr<class Aabb2DComp> aabbCollision_;

	Lamb::SafePtr<class InvisibleComp> invisible_;

	Lamb::SafePtr<class SpriteAnimatorComp> animation_;

	Lamb::Flg onGround_;

	std::unique_ptr<std::array<Vector3, 4>> prePositions_;

	Vector3 velocity_{};

	Vector3 tmpPosition_{ 0.0f,0.0f,1.0f };


#pragma region 菊谷が追加 2024/9/8
	Lamb::Flg beamCollisionFlg_;
#pragma endregion

};