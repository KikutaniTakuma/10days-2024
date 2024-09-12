#pragma once
#include "../Object.h"

class UvOperatorComp : public IComp {
public:

	using IComp::IComp;

	~UvOperatorComp() = default;

	void Init() override;

	void Move() override;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	Lamb::SafePtr<class TransformComp> transform_;

};
