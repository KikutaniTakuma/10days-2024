#include "ObbManager.h"

std::unique_ptr<ObbManager> ObbManager::instance_;

ObbManager::~ObbManager() {
	obbComps_.clear();
	obbPushComps_.clear();
}

ObbManager* const ObbManager::GetInstance()
{
	return instance_.get();
}

void ObbManager::Initialize()
{
	if (instance_) {
		return;
	}
	instance_.reset(new ObbManager());
}

void ObbManager::Finalize() {
	instance_.reset();
}

void ObbManager::Set(const Lamb::SafePtr<ObbComp>& obbComp) {
	if (not obbComps_.contains(obbComp)) {
		obbComps_.insert(obbComp);
	}
}
void ObbManager::Set(const Lamb::SafePtr<ObbPushComp>& obbPushComp) {
	if (not obbPushComps_.contains(obbPushComp)) {
		obbPushComps_.insert(obbPushComp);
	}
}

void ObbManager::Erase(const Lamb::SafePtr<ObbComp>& obbComp) {
	if (obbComps_.contains(obbComp)) {
		obbComps_.erase(obbComp);
	}
}

void ObbManager::Erase(const Lamb::SafePtr<ObbPushComp>& obbPushComp) {
	if (obbPushComps_.contains(obbPushComp)) {
		obbPushComps_.erase(obbPushComp);
	}
}

void ObbManager::Collision() {
	// 当たり判定(押し出し)
	for (auto i = obbPushComps_.begin(); i != obbPushComps_.end(); i++) {
		// 二重forで全部と当たり判定を取ると同じ組み合わせで2回当たり判定をとってしまうので
		// 2番目のループで1ループの値で初期化する
		for (auto j = i; j != obbPushComps_.end(); j++) {
			if (j == i) {
				continue;
			}
			// 当たり判定(押し出し)
			(*i)->Collision(&(*j)->GetObbComp());
		}
	}
	// 当たり判定(押し出し)
	for (auto i = obbComps_.begin(); i != obbComps_.end(); i++) {
		// 二重forで全部と当たり判定を取ると同じ組み合わせで2回当たり判定をとってしまうので
		// 2番目のループで1ループの値で初期化する
		for (auto j = i; j != obbComps_.end(); j++) {
			if (j == i) {
				continue;
			}
			// 当たり判定(押し出さない)
			(*i)->CollisionHasTag((*j).get());
		}
	}
}

void ObbManager::Clear()
{
	obbComps_.clear();
	obbPushComps_.clear();
}
