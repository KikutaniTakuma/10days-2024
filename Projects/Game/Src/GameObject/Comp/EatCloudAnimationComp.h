#pragma once
#include "../Object.h"
#include "Utils/Easeing.h"

class EatCloudAnimationComp : public IComp {
public:
	using IComp::IComp;

	~EatCloudAnimationComp() = default;

public:
	void Init() override;

	// 引っ張られる
	void PullStart();

private:
	// 元に戻る
	void ReturnStart();

public:
	void FirstUpdate() override;
	void Update() override;
	void LastUpdate() override;

	// 食べられたときのプレイヤーの向き
	void SetIsLeft(bool isLeft);

	void Debug(const std::string& guiName);

	Lamb::SafePtr<class TransformComp> GetTransformComp();
	Lamb::SafePtr<class SpriteRenderDataComp> GetSpriteRenderDataComp();

public:
	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:
	Lamb::SafePtr<class TransformComp> transformComp_;
	Lamb::SafePtr<class SpriteRenderDataComp> spriteRenderDataComp_;
	Lamb::SafePtr<class SpriteRenderComp> spriteRenderComp_;

	float32_t pullTime_ = 0.2f;
	float32_t returnTime_ = 0.3f;

	Easeing::Type pullType_ = Easeing::Type::kOutQuart;
	Easeing::Type returnType_ = Easeing::Type::kOutElastic;
	
	bool isReturnTime_ = false;

	Easeing ease_;
	Easeing colorEase_;
	
	float32_t2 colorAlphaMagnification_;
	float32_t colorEaseStartT = 0.5f;
	bool isClorEaseStart_ = false;

	float32_t2 scaleMagnification_;
	float32_t defaultScale_ = 0.0f;

	bool isFirstUpdate_ = false;
};
