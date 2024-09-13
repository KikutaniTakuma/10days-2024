#pragma once
#include "../Object.h"
#include <vector>

class ResultInputComp : public IComp {
public:

	using IComp::IComp;

	~ResultInputComp() = default;

	void Init() override;
	void Load() override;

	void Move() override;

	void Debug(const std::string& guiName) override;

	void SetGoal(class GoalComp* goalComp);

	void SetPlayer(class PlayerComp* player);

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	Lamb::SafePtr<class SceneChangeComp> sceneChangeComp_;

	//ゴールのポインタ
	Lamb::SafePtr<class GoalComp> goalComp_;

	Lamb::SafePtr <class SpriteRenderComp> spriteRenderComp_;

	Lamb::SafePtr <class UISpriteRenderDataComp> spriteRenderDataComp_;

	Lamb::SafePtr<class TransformComp> transform_;

	Lamb::SafePtr<class EaseingComp> easing_;

	Lamb::SafePtr<class Audio> audio_;

	Lamb::SafePtr <class UIDrawComp> UIDraw_;

	Lamb::SafePtr <class UITransformComp> UITransform_;

	Lamb::SafePtr<class Audio> backAudio_;
	Lamb::SafePtr<class Audio> decideAudio_;

	Lamb::SafePtr <class ChildrenObjectComp> childrenComp_;

	Lamb::SafePtr<class PlayerComp> player_;

	std::vector<Lamb::SafePtr<class StarComp>> stars_;

	std::vector<Lamb::SafePtr<class UIDrawComp>> buttonUIs_;

	std::vector<Lamb::SafePtr<class UINumSpriteComp>> nums_;

	Vector3 easingPositionStart_ = { 0.0f,-500.0f,-2.0f };

	Vector3 easingPositionEnd_ = { 0.0f,-0.0f,-2.0f };

	bool isEasingStart_ = false;

};
