#pragma once
#include "../Object.h"
class EyeComp : public IComp {
public:
	using IComp::IComp;

	~EyeComp() = default;

public:
	void Init() override;


private:
	// これは別のオブジェクトが持っているPlayerComp
	Lamb::SafePtr<class PlayerComp> playerComp_;

	Lamb::SafePtr<class TransformComp> transformComp_;


	Lamb::SafePtr<class ChildrenComp> eyeLine_;
};
