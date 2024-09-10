#pragma once
#include "../Object.h"
class CloudRenderComp : public IComp {
public:
	using IComp::IComp;

	~CloudRenderComp() = default;

public:
	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

public:
	void Init() override;

	void FirstUpdate() override;

	void Debug(const std::string& guiName);

private:
	bool isFirstUpdate_ = false;
	Lamb::SafePtr<class SpriteRenderDataComp> spriteRenderDataComp_;
};
