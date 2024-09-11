#pragma once
#include "../Object.h"

class GoalComp : public IComp {
public:

	using IComp::IComp;

	void Init() override;

	void Event() override;

	void Update() override;

	void SetPlayerComp(class PlayerComp* playerComp);

	~GoalComp() = default;

	const Lamb::Flg& GetIsGoal() const;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:
	//プレイヤーのポインタ
	Lamb::SafePtr<class PlayerComp> player_;
	//プレイヤーのAabb2DComp
	Lamb::SafePtr <class Aabb2DComp> playerAabbCollision_;
private:

	Lamb::SafePtr<class TransformComp> transformComp_;

	Lamb::SafePtr<class SpriteRenderComp> spriteRenderComp_;

	Lamb::SafePtr<class Aabb2DComp> aabbCollision_;

	Lamb::SafePtr<class Mass2DComp> mass_;

	Lamb::SafePtr<class FlagComp> isGoal_;

	Lamb::SafePtr<class SpriteAnimatorComp> animation_;

};
