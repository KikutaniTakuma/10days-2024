#pragma once
#include "../Object.h"

class CollectionComp : public IComp {
public:

	using IComp::IComp;

	void Init() override;

	void Event() override;

	~CollectionComp() = default;

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	Lamb::SafePtr<class TransformComp> transformComp_;

	Lamb::SafePtr<class SpriteRenderComp> spriteRenderComp_;

	Lamb::SafePtr<class ObbComp> collision_;

	Lamb::SafePtr<class Mass2DComp> mass_;

	Lamb::SafePtr<class Aabb2DComp> aabbCollision_;

};
