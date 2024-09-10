#include "InvisibleComp.h"
#include "CountComp.h"

void InvisibleComp::Init()
{
	count_ = object_.AddComp<CountComp>();
}

void InvisibleComp::FirstUpdate()
{
	//現在の雲のカウントが規定値を超えたら透明化フラグオン
	if (count_->GetCount() >= invisibleCount_) {
		isInvisible_ = true;
	}
	else {
		isInvisible_ = false;
	}

}

void InvisibleComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void InvisibleComp::Load([[maybe_unused]] nlohmann::json& json) {

}

