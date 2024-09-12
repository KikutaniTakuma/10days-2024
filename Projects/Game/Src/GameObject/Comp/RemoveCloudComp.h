#pragma once
 #include "../Object.h"
#include "../Manager/CloudManager.h"

 class RemoveCloudComp : public IComp {
 public:

	 using IComp::IComp;

	 ~RemoveCloudComp() = default;

	 void Load() override;

	 void Init() override;

	 void FirstUpdate() override;

	 void Event() override;

	 void LastUpdate() override;

	 void Finalize() override;

 public:

	 void Save(nlohmann::json& json) override;
	 void Load(nlohmann::json& json) override;

	 Lamb::Flg isRemove_;

 private:

	 Lamb::SafePtr<class TransformComp> transform_;

	 Lamb::SafePtr<class Direction2DComp> direction_;

	 Lamb::SafePtr<class CsvDataComp> csvData_;

	 Lamb::SafePtr<class Mass2DComp> mass_;

	 Lamb::SafePtr<class CountComp> count_;

	 Lamb::SafePtr<class Audio> removeCloudAudio_;
	 bool isStartAudio_ = false;
 };

