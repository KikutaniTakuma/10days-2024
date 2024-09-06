#pragma once
 #include "../Object.h"

 class RemoveCloudComp : public IComp {
 public:

	 using IComp::IComp;

	 ~RemoveCloudComp() = default;

	 void Event() override;

	 void Update() override;

 public:

	 void Save(nlohmann::json& json) override;
	 void Load(nlohmann::json& json) override;



 };

