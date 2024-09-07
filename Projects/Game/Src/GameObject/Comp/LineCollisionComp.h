#pragma once
#include "../Object.h"

#include "LineComp.h"
#include "ObbComp.h"
#include "TransformComp.h"

class LineCollisionComp : public IComp {
public:
	using IComp::IComp;

	~LineCollisionComp() = default;

public:
	void Init() override;

	void FirstUpdate() override;
	void LastUpdate() override;

	bool IsCollisionHasTag(ObbComp* obbComp);

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

	void Debug(const std::string& guiName) override;

	const LineComp& GetLineComp() const;
	const ObbComp& GetObbComp() const;

private:
	Lamb::SafePtr<LineComp> lineComp_;
	Lamb::SafePtr<ObbComp> obbComp_;
	Lamb::SafePtr<TransformComp> transFormComp_;

	std::unordered_set<std::string> collisionTags_;

	Lamb::Flg isCollision_;

	std::string currentCollisionTag_;
#ifdef _DEBUG
private:
	std::string inputTag_;
	uint32_t color_ = 0xffffffff;
#endif // _DEBUG
};
