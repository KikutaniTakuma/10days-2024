#pragma once
 #include "../Object.h"

 class EatCloudComp : public IComp {
 public:

	 using IComp::IComp;

	 ~EatCloudComp() = default;

	 void Event() override;

	 void Update() override;

 public:

	 void Save(nlohmann::json& json) override;
	 void Load(nlohmann::json& json) override;

	 Lamb::Flg isEat_;



 };

