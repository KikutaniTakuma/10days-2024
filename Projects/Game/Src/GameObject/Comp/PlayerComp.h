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

private:

	bool OnGround();

private:

	Lamb::SafePtr<class TransformComp> transform_;

	Lamb::SafePtr<class SpriteRenderComp> sprite_;

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

	Lamb::Flg onGround_;

	Vector3 velocity_{};

};