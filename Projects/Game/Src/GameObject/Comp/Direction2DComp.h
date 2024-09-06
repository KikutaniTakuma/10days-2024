#pragma once
 #include "../Object.h"

 class Direction2DComp : public IComp {
 public:

	 using IComp::IComp;

	 ~Direction2DComp() = default;

	 bool IsLeft() { return direction_.x < 0.0f and fabsf(direction_.y < 0.5f); }

	 bool IsRight() { return direction_.x > 0.0f and fabsf(direction_.y < 0.5f); }

	 bool IsUp() { return direction_.y > 0.0f and fabsf(direction_.x <= 0.5f); }

	 bool IsDown() {return direction_.y < 0.0f and fabsf(direction_.x <= 0.5f); }

	 Vector2 direction_{};

 public:

	 

	 void Save(nlohmann::json& json) override;
	 void Load(nlohmann::json& json) override;

 private:

 };