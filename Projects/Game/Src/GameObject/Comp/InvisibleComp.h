#pragma once
#include "../Object.h"

class InvisibleComp : public IComp {
public:

	using IComp::IComp;

	void Init() override;

	~InvisibleComp() = default;

	void FirstUpdate() override;

	const Lamb::Flg& GetIsInvisible() const {
		return isInvisible_;
	}

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	Lamb::SafePtr<class CountComp> count_;

	//透明に必要な雲の個数
	int32_t invisibleCount_ = 5;

	//透明かどうかのフラグ
	Lamb::Flg isInvisible_;

};
