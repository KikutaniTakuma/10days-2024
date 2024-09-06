#pragma once
#include "../Object.h"
class LineRenderDataComp : public IComp {
public:
	using IComp::IComp;

	~LineRenderDataComp() = default;

public:
	void Init() override;

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	void Debug(const std::string& guiName);

public:
	Vector4 color;
	bool isDepth = false;

private:
	Lamb::SafePtr<class LineComp> lineComp_;
};
