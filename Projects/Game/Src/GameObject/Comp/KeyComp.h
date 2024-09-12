#pragma once
#include "../Object.h"

class KeyComp : public IComp {
public:

	using IComp::IComp;

	void Init() override;

	void Load() override;
	void LastUpdate() override;

	void Finalize() override;

	void Event() override;

	~KeyComp() = default;

	void SetPlayerComp(class PlayerComp* playerComp);

	void SetIsObtained(bool flag) { isObtained_ = flag; }

	const Lamb::Flg& GetIsObtained() const { return isObtained_; }

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

	Lamb::SafePtr<class Mass2DComp> mass_;

	Lamb::SafePtr<class Aabb2DComp> aabbCollision_;

	Lamb::Flg isObtained_;

	Lamb::SafePtr<class Audio> getKeyAudio_;
};
