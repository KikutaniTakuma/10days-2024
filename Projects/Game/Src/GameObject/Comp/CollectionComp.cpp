#include "CollectionComp.h"
#include "TransformComp.h"
#include "SpriteRenderComp.h"
#include "ObbComp.h"
#include "Mass2DComp.h"
#include "Aabb2DComp.h"

void CollectionComp::Init()
{
	transformComp_ = object_.AddComp<TransformComp>();
	spriteRenderComp_ = object_.AddComp<SpriteRenderComp>();
	collision_ = object_.AddComp<ObbComp>();
	mass_ = object_.AddComp<Mass2DComp>();
	aabbCollision_ = object_.AddComp<Aabb2DComp>();
}

void CollectionComp::Event()
{



}

void CollectionComp::Save(nlohmann::json& json) {
	SaveCompName(json);
}

void CollectionComp::Load([[maybe_unused]] nlohmann::json& json) {

}

