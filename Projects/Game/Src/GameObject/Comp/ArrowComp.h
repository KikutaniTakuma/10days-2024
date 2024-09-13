#pragma once
#include "../Object.h"

class ArrowComp : public IComp {
public:

	using IComp::IComp;

	void Init() override;

	void Move() override;

	~ArrowComp() = default;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	Lamb::SafePtr<class UITransformComp> transform_;

	bool isLeft_ = false;

};

