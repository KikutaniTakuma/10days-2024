#pragma once
#include "../Object.h"
class CloudRenderComp : public IComp {
public:
	using IComp::IComp;

	~CloudRenderComp() = default;

public:
	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	void Load() override;

public:
	void Init() override;

	void FirstUpdate() override;

	void Update() override;
	void LastUpdate() override;

	void Debug(const std::string& guiName);

private:
	bool isFirstUpdate_ = false;
	Lamb::SafePtr<class SpriteRenderDataComp> spriteRenderDataComp_;
	Lamb::SafePtr<class EaseingComp> easeingComp_;
	Lamb::SafePtr<class TransformComp> transformComp_;
	Lamb::SafePtr<class InstanceTimeComp> instanceTimeComp_;
	
	// もくもくの拡縮開始時間(ランダム)
	float32_t easeStartTime_ = 0.0f;
	float32_t2 randDuration_;
	float32_t scaleMax_ = 0.0f;
	float32_t3 scale_;
	

};
