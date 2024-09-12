#include "EatAnimationControllComp.h"
#include "ChildrenObjectComp.h"
#include "TransformComp.h"
#include "SpriteRenderDataComp.h"

void EatAnimationControllComp::Save(nlohmann::json& json)
{
	SaveCompName(json);
}

void EatAnimationControllComp::Load([[maybe_unused]]nlohmann::json& json) {

}

void EatAnimationControllComp::Load() {
	childrenComp_->Clear();

	eatCloudAnimationComps_.reserve(childrenSize_);



	/// ===================================================================
	/// ハイパーウルトラごりおしいいいいいいいいいい！！！！！！！！！
	/// ===================================================================
	
	Lamb::SafePtr<Object> newObject = Lamb::MakeSafePtr<Object>();
	eatCloudAnimationComps_.push_back(newObject->AddComp<EatCloudAnimationComp>());
	auto transform = eatCloudAnimationComps_.back()->GetTransformComp();
	transform->translate = { 0.5546870231628418f, -0.08593793213367462f, 0.0f };
	transform->scale = { 0.4343995153903961f,0.4047611355781555f, 1.0f };
	auto renderData = eatCloudAnimationComps_.back()->GetSpriteRenderDataComp();
	renderData->fileName = "./Resources/Textures//gimmick/cloud_shadow1.png";
	renderData->offsetType = SpriteRenderDataComp::Offset::kLeft;
	renderData->uvTransform.scale.x = 0.25f;
	renderData->Load();
	childrenComp_->AddObject(newObject);

	newObject = Lamb::MakeSafePtr<Object>();
	eatCloudAnimationComps_.push_back(newObject->AddComp<EatCloudAnimationComp>());
	transform = eatCloudAnimationComps_.back()->GetTransformComp();
	transform->translate = { 0.26471126079559326f,
										0.359376460313797f,
										0.0f };
	transform->scale = { 0.3505116105079651f,
										0.3216201066970825f,
										1.0f };
	renderData = eatCloudAnimationComps_.back()->GetSpriteRenderDataComp();
	renderData->fileName = "./Resources/Textures//gimmick/cloud_shadow1.png";
	renderData->offsetType = SpriteRenderDataComp::Offset::kLeft;
	renderData->uvTransform.scale.x = 0.25f;
	renderData->Load();
	childrenComp_->AddObject(newObject);

	newObject = Lamb::MakeSafePtr<Object>();
	eatCloudAnimationComps_.push_back(newObject->AddComp<EatCloudAnimationComp>());
	transform = eatCloudAnimationComps_.back()->GetTransformComp();
	transform->translate = { 0.5078127384185791f,
										0.22656220197677612f,
										0.0f };
	transform->scale = { 0.3555077612400055f,
										0.4428665339946747f,
										1.0f };
	renderData = eatCloudAnimationComps_.back()->GetSpriteRenderDataComp();
	renderData->fileName = "./Resources/Textures//gimmick/cloud_shadow1.png";
	renderData->offsetType = SpriteRenderDataComp::Offset::kLeft;
	renderData->uvTransform.scale.x = 0.25f;
	renderData->Load();
	childrenComp_->AddObject(newObject);

	newObject = Lamb::MakeSafePtr<Object>();
	eatCloudAnimationComps_.push_back(newObject->AddComp<EatCloudAnimationComp>());
	transform = eatCloudAnimationComps_.back()->GetTransformComp();
	transform->translate = { 0.38281217217445374f,
										-0.38281217217445374f,
										0.0f };
	transform->scale = { 0.3958333730697632f,
										0.3055548071861267f,
										1.0f };
	renderData = eatCloudAnimationComps_.back()->GetSpriteRenderDataComp();
	renderData->fileName = "./Resources/Textures//gimmick/cloud_shadow1.png";
	renderData->offsetType = SpriteRenderDataComp::Offset::kLeft;
	renderData->uvTransform.scale.x = 0.25f;
	renderData->Load();
	childrenComp_->AddObject(newObject);

	newObject = Lamb::MakeSafePtr<Object>();
	eatCloudAnimationComps_.push_back(newObject->AddComp<EatCloudAnimationComp>());
	transform = eatCloudAnimationComps_.back()->GetTransformComp();
	transform->translate = { 0.5312492847442627f,
										0.5078122615814209f,
										0.0f };
	transform->scale = { 0.3333328366279602f,
										0.2272728979587555f,
										1.0f };
	renderData = eatCloudAnimationComps_.back()->GetSpriteRenderDataComp();
	renderData->fileName = "./Resources/Textures//gimmick/cloud_shadow1.png";
	renderData->offsetType = SpriteRenderDataComp::Offset::kLeft;
	renderData->uvTransform.scale.x = 0.25f;
	renderData->Load();
	childrenComp_->AddObject(newObject);

	newObject = Lamb::MakeSafePtr<Object>();
	eatCloudAnimationComps_.push_back(newObject->AddComp<EatCloudAnimationComp>());
	transform = eatCloudAnimationComps_.back()->GetTransformComp();
	transform->translate = { 0.5937501192092896f,
										-0.4218751788139343f,
										0.0f };
	transform->scale = { 0.26363620162010193f,
										0.2796056866645813f,
										1.0f };
	renderData = eatCloudAnimationComps_.back()->GetSpriteRenderDataComp();
	renderData->fileName = "./Resources/Textures//gimmick/cloud_shadow1.png";
	renderData->offsetType = SpriteRenderDataComp::Offset::kLeft;
	renderData->uvTransform.scale.x = 0.25f;
	renderData->Load();
	childrenComp_->AddObject(newObject);
}

void EatAnimationControllComp::Init() {
	childrenComp_ = object_.AddComp<decltype(childrenComp_)::type>();

}

void EatAnimationControllComp::SetIsLeft(bool isLeft) {
	for (auto& i : eatCloudAnimationComps_) {
		i->SetIsLeft(isLeft);
	}
}

void EatAnimationControllComp::StartAnimation() {
	for (auto& i : eatCloudAnimationComps_) {
		i->PullStart();
	}
}
