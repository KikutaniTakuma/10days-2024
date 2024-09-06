#pragma once
 #include "../Object.h"

 class CountComp : public IComp {
 public:

	 using IComp::IComp;

	 ~CountComp() = default;

	 void Event() override;

	 void Update() override;

 public:

	 void Save(nlohmann::json& json) override;
	 void Load(nlohmann::json& json) override;

	 int32_t count;

 };

