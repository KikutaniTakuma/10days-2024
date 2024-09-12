#include "UvOperatorComp.h"
#include "TransformComp.h"

void UvOperatorComp::Init()
{
	transform_ = object_.AddComp<TransformComp>();
}

void UvOperatorComp::Move()
{

	

}

void UvOperatorComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void UvOperatorComp::Load([[maybe_unused]] nlohmann::json& json) {

}

