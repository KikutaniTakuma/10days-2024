#pragma once
 #include "../Object.h"

 class Direction2DComp : public IComp {
 public:

	 using IComp::IComp;

	 ~Direction2DComp() = default;
		
 public:

	 void Save(nlohmann::json& json) override;
	 void Load(nlohmann::json& json) override;



 };