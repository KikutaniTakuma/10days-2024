#pragma once
#include "../Object.h"

class ArrowComp : public IComp {
public:

	using IComp::IComp;

	void Init() override;

	void Move() override;

	void Debug(const std::string& guiName) override;

	~ArrowComp() = default;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	Lamb::SafePtr<class UITransformComp> transform_;

	bool isLeft_ = false;

	bool isStickUsed_ = false;

	float startX_ = 0.0f;
	float moveValue_ = 100.0f;
	float backValue_ = 1.0f;

};

