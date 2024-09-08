#pragma once
#include "../Object.h"

class KeyComp : public IComp {
public:

	using IComp::IComp;

	void Init() override;

	~KeyComp() = default;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	Lamb::SafePtr<class TransformComp> transformComp_;

	Lamb::SafePtr<class SpriteRenderComp> spriteRenderComp_;

	Lamb::SafePtr<class ObbPushComp> collision_;

	Lamb::SafePtr<class Mass2DComp> mass_;

};
