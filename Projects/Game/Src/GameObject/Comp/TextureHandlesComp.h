#pragma once
#include "../Object.h"
#include <vector>
#include <string>

class TextureHandlesComp : public IComp {
public:

	using IComp::IComp;

	void Init() override;

	~TextureHandlesComp() = default;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	std::vector<uint32_t> textureHandles_;
	std::vector<std::string> fileNames_;

private:

	
};
