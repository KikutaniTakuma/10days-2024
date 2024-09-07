#pragma once
#include "../Object.h"

class Mass2DComp : public IComp {
public:

	using IComp::IComp;

	~Mass2DComp() = default;

	void Init() override;

	void Move() override;

	void SetXOffset(float offset) { offsetX_ = offset; }
	void SetYOffset(float offset) { offsetY_ = offset; }

	void SetMassSize(int32_t size) { massSize_ = size; }

	int32_t GetMassX() const { return massX_; }
	int32_t GetMassY() const { return massY_; }

public:

	void Save(nlohmann::json& json) override;
	void Load(nlohmann::json& json) override;

private:

	Lamb::SafePtr<class TransformComp> transform_;

	int32_t massX_;
	int32_t massY_;

	int32_t massSize_ = 32;

	float32_t offsetX_ = 0.0f;
	float32_t offsetY_ = 0.0f;

};

