#include "Aabb2DManager.h"

std::unique_ptr<Aabb2DManager> Aabb2DManager::instance_;

Aabb2DManager::~Aabb2DManager() {
	aabb2DComps_.clear();
}

Aabb2DManager* const Aabb2DManager::GetInstance()
{
	return instance_.get();
}

void Aabb2DManager::Initialize()
{
	if (instance_) {
		return;
	}
	instance_.reset(new Aabb2DManager());
}

void Aabb2DManager::Finalize() {
	instance_.reset();
}

void Aabb2DManager::Set(const Lamb::SafePtr<Aabb2DComp>& aabb2DComp) {
	if (not aabb2DComps_.contains(aabb2DComp)) {
		aabb2DComps_.insert(aabb2DComp);
	}
}

void Aabb2DManager::Erase(const Lamb::SafePtr<Aabb2DComp>& aabb2DComp) {
	if (aabb2DComps_.contains(aabb2DComp)) {
		aabb2DComps_.erase(aabb2DComp);
	}
}


void Aabb2DManager::Collision() {
	
	// 当たり判定
	for (auto i = aabb2DComps_.begin(); i != aabb2DComps_.end(); i++) {
		for (auto j = aabb2DComps_.begin(); j != aabb2DComps_.end(); j++) {
			if (j == i) {
				continue;
			}
			// 当たり判定
			(*i)->CollisionHasTag((*j).get());
		}
	}
}

void Aabb2DManager::Clear()
{
	aabb2DComps_.clear();
}
