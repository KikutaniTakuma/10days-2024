#include "Mass2DComp.h"
#include "TransformComp.h"

void Mass2DComp::Init()
{

	transform_ = object_.AddComp<TransformComp>();

}

void Mass2DComp::Move()
{

	if (massSize_ != 0) {
		massX_ = int32_t(transform_->translate.x + offsetX_) / massSize_;
		massY_ = int32_t(-transform_->translate.y + offsetY_) / massSize_;
	}

}

void Mass2DComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
	json["mass"] = nlohmann::json::array();
	json["mass"].push_back(massX_);
	json["mass"].push_back(massY_);
	json["offset"] = nlohmann::json::array();
	json["offset"].push_back(offsetX_);
	json["offset"].push_back(offsetY_);
	json["size"] = massSize_;

}

void Mass2DComp::Load([[maybe_unused]] nlohmann::json& json)
{

	massX_ = json["mass"][0];
	massY_ = json["mass"][1];
	offsetX_ = json["offset"][0];
	offsetY_ = json["offset"][1];
	massSize_ = json["size"];


}
