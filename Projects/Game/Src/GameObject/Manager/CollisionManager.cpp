#include "CollisionManager.h"
#include "../Comp/LineCollisionComp.h"
#include "../Comp/LineComp.h"

std::unique_ptr<CollisionManager> CollisionManager::instance_;

CollisionManager::~CollisionManager() {
	obbComps_.clear();
	obbPushComps_.clear();
}

CollisionManager* const CollisionManager::GetInstance()
{
	return instance_.get();
}

void CollisionManager::Initialize()
{
	if (instance_) {
		return;
	}
	instance_.reset(new CollisionManager());
}

void CollisionManager::Finalize() {
	instance_.reset();
}


void CollisionManager::Set(const Lamb::SafePtr<ObbComp>& obbComp) {
	if (not obbComps_.contains(obbComp)) {
		obbComps_.insert(obbComp);
	}
}
void CollisionManager::Erase(const Lamb::SafePtr<ObbComp>& obbComp) {
	if (obbComps_.contains(obbComp)) {
		obbComps_.erase(obbComp);
	}
}

void CollisionManager::Set(const Lamb::SafePtr<ObbPushComp>& obbPushComp) {
	if (not obbPushComps_.contains(obbPushComp)) {
		obbPushComps_.insert(obbPushComp);
	}
}
void CollisionManager::Erase(const Lamb::SafePtr<ObbPushComp>& obbPushComp) {
	if (obbPushComps_.contains(obbPushComp)) {
		obbPushComps_.erase(obbPushComp);
	}
}

void CollisionManager::Set(const Lamb::SafePtr<LineCollisionComp>& lineCollisionComp) {
	if (not lineCollisionComps_.contains(lineCollisionComp)) {
		lineCollisionComps_.insert(lineCollisionComp);
	}
}
void CollisionManager::Erase(const Lamb::SafePtr<LineCollisionComp>& lineCollisionComp) {
	if (lineCollisionComps_.contains(lineCollisionComp)) {
		lineCollisionComps_.erase(lineCollisionComp);
	}
}

void CollisionManager::Collision() {
	for (auto& i : collisionPairsObbObb_) {
		i.first->Collision(i.second.get());
	}
	for (auto& i : collisionPairsObbPushObbPush_) {
		i.first->Collision(i.second.get());
	}
	for (auto& i : collisionPairsObbLine_) {
		i.first->Collision(i.second.get());
	}
}

void CollisionManager::Clear()
{
	obbComps_.clear();
	obbPushComps_.clear();
	lineCollisionComps_.clear();
	collisionPairsObbObb_.clear();
	collisionPairsObbPushObbPush_.clear();
	collisionPairsObbLine_.clear();
}

void CollisionManager::MakeCollisionPair() {
	collisionPairsObbObb_.clear();
	collisionPairsObbObb_.reserve(obbComps_.size());
	collisionPairsObbPushObbPush_.clear();
	collisionPairsObbPushObbPush_.reserve(obbPushComps_.size());
	collisionPairsObbLine_.clear();
	collisionPairsObbLine_.reserve(lineCollisionComps_.size());

	// 当たり判定(押し出し)
	for (auto i = obbPushComps_.begin(); i != obbPushComps_.end(); i++) {
		for (auto j = obbPushComps_.begin(); j != obbPushComps_.end(); j++) {
			if (j == i) {
				continue;
			}
			for (auto& tag : i->get()->GetCollisionTagList()) {
				if (j->get()->getObject().HasTag(tag)) {
					collisionPairsObbPushObbPush_.push_back(std::make_pair(*i, *j));
				}
			}
		}
	}
	// 当たり判定
	for (auto i = obbComps_.begin(); i != obbComps_.end(); i++) {
		for (auto j = obbComps_.begin(); j != obbComps_.end(); j++) {
			if (j == i) {
				continue;
			}
			for (auto& tag : i->get()->GetCollisionTagList()) {
				if (j->get()->getObject().HasTag(tag)) {
					collisionPairsObbObb_.push_back(std::make_pair(*i, *j));
				}
			}
		}
	}

	// 当たり判定(線分)
	for (auto i = lineCollisionComps_.begin(); i != lineCollisionComps_.end(); i++) {
		for (auto j = obbComps_.begin(); j != obbComps_.end(); j++) {
			for (auto& tag : i->get()->GetCollisionTagList()) {
				if (j->get()->getObject().HasTag(tag)) {
					collisionPairsObbLine_.push_back(std::make_pair(*i, *j));
				}
			}
		}
	}
}
