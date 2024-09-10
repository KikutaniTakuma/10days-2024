#pragma once
 #include "../Object.h"
#include "../Manager/CloudManager.h"

 class EatCloudComp : public IComp {
 public:

	 using IComp::IComp;

	 ~EatCloudComp() = default;

	 void FirstUpdate() override;

	 void Init() override;

	 void Event() override;

	 void Update() override;

 public:

	 void Save(nlohmann::json& json) override;
	 void Load(nlohmann::json& json) override;

	 Lamb::Flg isEat_;

 private:

	 Lamb::SafePtr<class TransformComp> transform_;

	 Lamb::SafePtr<class Direction2DComp> direction_;

	 Lamb::SafePtr<class CsvDataComp> csvData_;

	 Lamb::SafePtr<class Mass2DComp> mass_;

	 Lamb::SafePtr<class CountComp> count_;

 };

