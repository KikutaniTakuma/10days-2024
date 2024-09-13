#pragma once
#include "../Object.h"

class ResultInputComp : public IComp {
public:

	using IComp::IComp;

	~ResultInputComp() = default;

	void Init() override;
	void Load() override;

	void Move() override;

	void Debug(const std::string& guiName) override;

	void SetGoal(class GoalComp* goalComp);

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	Lamb::SafePtr<class SceneChangeComp> sceneChangeComp_;

	//ゴールのポインタ
	Lamb::SafePtr<class GoalComp> goalComp_;

	Lamb::SafePtr <class SpriteRenderComp> spriteRenderComp_;

	Lamb::SafePtr <class SpriteRenderDataComp> spriteRenderDataComp_;

	Lamb::SafePtr<class TransformComp> transform_;

	Lamb::SafePtr<class EaseingComp> easing_;

	Lamb::SafePtr<class Audio> audio_;
};
