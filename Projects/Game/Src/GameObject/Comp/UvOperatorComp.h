#pragma once
#include "../Object.h"

class UvOperatorComp : public IComp {
public:

	using IComp::IComp;

	~UvOperatorComp() = default;

	void Init() override;

	void Move() override;

	void Debug(const std::string& guiName) override;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	Lamb::SafePtr<class SpriteRenderDataComp> spriteRenderDataComp_;

	Vector3 moveValue_ = { 0.0f,0.0f,0.0f };

	bool isStartMove_ = false;

};
