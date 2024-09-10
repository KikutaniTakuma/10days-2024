#pragma once
 #include "../Object.h"

 class CountComp : public IComp {
 public:

	 using IComp::IComp;

	 ~CountComp() = default;

	 void AddCount(int32_t num) { count += num; }

	 void ResetCount(int32_t num) { count = num; }

	 int32_t GetCount() const { return count; }

 public:

	 void Save(nlohmann::json& json) override;
	 void Load(nlohmann::json& json) override;

 private:

	 int32_t count = 0;

 };

