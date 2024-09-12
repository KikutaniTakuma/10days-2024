#pragma once

#include "../Object.h"

class EventComp : public IComp {
public:
	using IComp::IComp;

	~EventComp() = default;

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	void Debug(const std::string& guiName) override;

public:
	Lamb::Flg isEvent;
};