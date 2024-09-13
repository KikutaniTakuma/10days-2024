#pragma once
#include "../Object.h"

class FlagComp : public IComp {
public:

	using IComp::IComp;

	~FlagComp() = default;

	const Lamb::Flg& GetIsActive() const { return isActive_; }

	void SetIsActive(bool isActive) { isActive_ = isActive; }

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	void Debug(const std::string& guiName) override;

private:

	Lamb::Flg isActive_;

};
