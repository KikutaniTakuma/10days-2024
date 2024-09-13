#include "CloudUIComp.h"
#include "ChildrenObjectComp.h"
#include "CountComp.h"
#include "UIDrawComp.h"
#include "SpriteRenderDataComp.h"
#include "UITransformComp.h"

void CloudUIComp::Init()
{
	childrenComp_ = object_.AddComp<ChildrenObjectComp>();
	spriteRenderDataComp_ = object_.AddComp<SpriteRenderDataComp>();
	UIDraw_ = object_.AddComp<UIDrawComp>();
	cloudsUI_.clear();
}

void CloudUIComp::Load()
{

	for (size_t i = 0; i < 20; i++) {

		Lamb::SafePtr<Object> newObject = Lamb::MakeSafePtr<Object>();
		cloudsUI_.push_back(newObject->AddComp<UIDrawComp>());
		auto transform = cloudsUI_.back()->getObject().GetComp<UITransformComp>();
		transform->translate = { 490.0f + 32.0f * float(i), 250.0f, -1.0f};
		transform->scale = { 32.0f,32.0f, 1.0f };
		auto renderData = cloudsUI_.back()->getObject().GetComp<SpriteRenderDataComp>();
		renderData->fileName = "./Resources/Textures/UI/ingame_cloudNum_outline.png";
		renderData->offsetType = SpriteRenderDataComp::Offset::kMiddle;
		renderData->Load();

	}

}

void CloudUIComp::Update()
{

	if (count_) {



	}

}

void CloudUIComp::SetCountComp(CountComp* countComp)
{

	count_ = countComp;

}

void CloudUIComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void CloudUIComp::Load([[maybe_unused]] nlohmann::json& json)
{
}
