#include "CloudUIComp.h"
#include "ChildrenObjectComp.h"
#include "CountComp.h"
#include "UIDrawComp.h"
#include "UISpriteRenderDataComp.h"
#include "UITransformComp.h"
#include "Engine/Graphics/TextureManager/TextureManager.h"
#include "SpriteUVChangeComp.h"

void CloudUIComp::Init()
{
	childrenComp_ = object_.AddComp<ChildrenObjectComp>();
	spriteRenderDataComp_ = object_.AddComp<UISpriteRenderDataComp>();
	UIDraw_ = object_.AddComp<UIDrawComp>();
	UItransform_ = object_.AddComp<UITransformComp>();
	count_ = object_.AddComp<CountComp>();
	cloudsUI_.clear();

}

void CloudUIComp::Load()
{
	TextureManager::GetInstance()->LoadTexture("./Resources/Textures/UI/ingame_cloudNum_backGround.png");
	TextureManager::GetInstance()->LoadTexture("./Resources/Textures/UI/ingame_cloudNum_outline.png");
	TextureManager::GetInstance()->LoadTexture("./Resources/Textures/UI/ingame_cloudNum_outline_transparent.png");

	parentUITexID_ = TextureManager::GetInstance()->GetTexture("./Resources/Textures/UI/ingame_cloudNum_backGround.png")->GetHandleUINT();
	cloudTexID_ = TextureManager::GetInstance()->GetTexture("./Resources/Textures/UI/ingame_cloudNum_outline.png")->GetHandleUINT();
	cloudOutlineLineTexID_ = TextureManager::GetInstance()->GetTexture("./Resources/Textures/UI/ingame_cloudNum_outline_transparent.png")->GetHandleUINT();
	
	UItransform_->translate = {
		494.9992370605469f,
						256.999267578125f,
						1.0f
	};
	UItransform_->scale = {
		270.6899108886719f,
						163.64881896972656f,
						1.0f
	};
	spriteRenderDataComp_->type = BlendType::kUnenableDepthNone;

	spriteRenderDataComp_->texHandle = parentUITexID_;

	spriteRenderDataComp_->uvTransform.rotate.vector4 = Vector4::kWIdentity;

	// 1
	Lamb::SafePtr<Object> newObject = Lamb::MakeSafePtr<Object>();
	newObject->AddComp<UIDrawComp>();
	cloudsUI_.push_back(newObject->AddComp<SpriteUVChangeComp>());
	auto transform = cloudsUI_.back()->GetUITransformComp();
	transform->translate = { -0.32315476989746094f,
										-0.12832403182983398f,
										-1.0f };
	transform->scale = { 0.1432291567325592f,
										0.19792717695236206f,
										1.0f };
	auto renderData = cloudsUI_.back()->GetSpriteRenderDataComp();
	renderData->texHandle = cloudTexID_;
	renderData->type = BlendType::kUnenableDepthNone;
	childrenComp_->AddObject(newObject);

	// 2
	newObject = Lamb::MakeSafePtr<Object>();
	newObject->AddComp<UIDrawComp>();
	cloudsUI_.push_back(newObject->AddComp<SpriteUVChangeComp>());
	transform = cloudsUI_.back()->GetUITransformComp();
	transform->translate = { -0.15565773105621338f,
										-0.12832415103912354f,
										-1.0f };
	transform->scale = { 0.1432291567325592f,
										0.19792717695236206f,
										1.0f };
	renderData = cloudsUI_.back()->GetSpriteRenderDataComp();
	renderData->texHandle = cloudTexID_;
	
	renderData->type = BlendType::kUnenableDepthNone;
	childrenComp_->AddObject(newObject);

	float sub = 0.32315476989746094f - 0.15565773105621338f;
	Vector3 pre = transform->translate;

	// 3
	newObject = Lamb::MakeSafePtr<Object>();
	newObject->AddComp<UIDrawComp>();
	cloudsUI_.push_back(newObject->AddComp<SpriteUVChangeComp>());
	transform = cloudsUI_.back()->GetUITransformComp();
	transform->translate = pre;
	transform->translate.x += sub;
	transform->scale = { 0.1432291567325592f,
										0.19792717695236206f,
										1.0f };
	renderData = cloudsUI_.back()->GetSpriteRenderDataComp();
	renderData->texHandle = cloudTexID_;
	
	renderData->type = BlendType::kUnenableDepthNone;
	childrenComp_->AddObject(newObject);

	pre = transform->translate;

	// 4
	newObject = Lamb::MakeSafePtr<Object>();
	newObject->AddComp<UIDrawComp>();
	cloudsUI_.push_back(newObject->AddComp<SpriteUVChangeComp>());
	transform = cloudsUI_.back()->GetUITransformComp();
	transform->translate = pre;
	transform->translate.x += sub;
	transform->scale = { 0.1432291567325592f,
										0.19792717695236206f,
										1.0f };
	renderData = cloudsUI_.back()->GetSpriteRenderDataComp();
	renderData->texHandle = cloudTexID_;
	
	renderData->type = BlendType::kUnenableDepthNone;
	childrenComp_->AddObject(newObject);

	pre = transform->translate;

	// 5
	newObject = Lamb::MakeSafePtr<Object>();
	newObject->AddComp<UIDrawComp>();
	cloudsUI_.push_back(newObject->AddComp<SpriteUVChangeComp>());
	transform = cloudsUI_.back()->GetUITransformComp();
	transform->translate = pre;
	transform->translate.x += sub;
	transform->scale = { 0.1432291567325592f,
										0.19792717695236206f,
										1.0f };
	renderData = cloudsUI_.back()->GetSpriteRenderDataComp();
	renderData->texHandle = cloudTexID_;
	
	renderData->type = BlendType::kUnenableDepthNone;
	childrenComp_->AddObject(newObject);

	pre = transform->translate;
	pre.x = -0.32315476989746094f - sub;
	pre.y += sub * 1.2f;

	// 6
	newObject = Lamb::MakeSafePtr<Object>();
	newObject->AddComp<UIDrawComp>();
	cloudsUI_.push_back(newObject->AddComp<SpriteUVChangeComp>());
	transform = cloudsUI_.back()->GetUITransformComp();
	transform->translate = pre;
	transform->translate.x += sub;
	transform->scale = { 0.1432291567325592f,
										0.19792717695236206f,
										1.0f };
	renderData = cloudsUI_.back()->GetSpriteRenderDataComp();
	renderData->texHandle = cloudOutlineLineTexID_;
	
	renderData->type = BlendType::kUnenableDepthNone;
	childrenComp_->AddObject(newObject);

	pre = transform->translate;

	// 7
	newObject = Lamb::MakeSafePtr<Object>();
	newObject->AddComp<UIDrawComp>();
	cloudsUI_.push_back(newObject->AddComp<SpriteUVChangeComp>());
	transform = cloudsUI_.back()->GetUITransformComp();
	transform->translate = pre;
	transform->translate.x += sub;
	transform->scale = { 0.1432291567325592f,
										0.19792717695236206f,
										1.0f };
	renderData = cloudsUI_.back()->GetSpriteRenderDataComp();
	renderData->texHandle = cloudOutlineLineTexID_;
	
	renderData->type = BlendType::kUnenableDepthNone;
	childrenComp_->AddObject(newObject);

	pre = transform->translate;


	// 8
	newObject = Lamb::MakeSafePtr<Object>();
	newObject->AddComp<UIDrawComp>();
	cloudsUI_.push_back(newObject->AddComp<SpriteUVChangeComp>());
	transform = cloudsUI_.back()->GetUITransformComp();
	transform->translate = pre;
	transform->translate.x += sub;
	transform->scale = { 0.1432291567325592f,
										0.19792717695236206f,
										1.0f };
	renderData = cloudsUI_.back()->GetSpriteRenderDataComp();
	renderData->texHandle = cloudOutlineLineTexID_;
	
	renderData->type = BlendType::kUnenableDepthNone;
	childrenComp_->AddObject(newObject);

	pre = transform->translate;

	// 9
	newObject = Lamb::MakeSafePtr<Object>();
	newObject->AddComp<UIDrawComp>();
	cloudsUI_.push_back(newObject->AddComp<SpriteUVChangeComp>());
	transform = cloudsUI_.back()->GetUITransformComp();
	transform->translate = pre;
	transform->translate.x += sub;
	transform->scale = { 0.1432291567325592f,
										0.19792717695236206f,
										1.0f };
	renderData = cloudsUI_.back()->GetSpriteRenderDataComp();
	renderData->texHandle = cloudOutlineLineTexID_;
	
	renderData->type = BlendType::kUnenableDepthNone;
	childrenComp_->AddObject(newObject);

	pre = transform->translate;

	// 10
	newObject = Lamb::MakeSafePtr<Object>();
	newObject->AddComp<UIDrawComp>();
	cloudsUI_.push_back(newObject->AddComp<SpriteUVChangeComp>());
	transform = cloudsUI_.back()->GetUITransformComp();
	transform->translate = pre;
	transform->translate.x += sub;
	transform->scale = { 0.1432291567325592f,
										0.19792717695236206f,
										1.0f };
	renderData = cloudsUI_.back()->GetSpriteRenderDataComp();
	renderData->texHandle = cloudOutlineLineTexID_;
	
	renderData->type = BlendType::kUnenableDepthNone;
	childrenComp_->AddObject(newObject);

	pre = transform->translate;
}

void CloudUIComp::Update()
{
	spriteRenderDataComp_->texHandle = parentUITexID_;


	if (count_) {
		for (int32_t count = 0; auto & i : cloudsUI_) {
			if (count <= count_->GetCount() - 1) {
				i->EnableFlag();
			}
			else {
				i->UnenableFlag();
			}

			count++;
		}


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
