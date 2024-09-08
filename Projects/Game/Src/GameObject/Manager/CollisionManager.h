#pragma once
#include <memory>
#include <unordered_set>

#include "Utils/SafePtr.h"

#include "../Comp/ObbPushComp.h"
#include "../Comp/LineCollisionComp.h"

class CollisionManager {
private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager(CollisionManager&&) = delete;

	CollisionManager& operator=(const CollisionManager&) = delete;
	CollisionManager& operator=(CollisionManager&&) = delete;

public:
	~CollisionManager();

public:
	static CollisionManager* const GetInstance();

	static void Initialize();

	static void Finalize();

private:
	static std::unique_ptr<CollisionManager> instance_;

public:
	void Set(const Lamb::SafePtr<ObbComp>& obbComp);
	void Erase(const Lamb::SafePtr<ObbComp>& obbComp);
	void Set(const Lamb::SafePtr<ObbPushComp>& obbPushComp);
	void Erase(const Lamb::SafePtr<ObbPushComp>& obbPushComp);
	void Set(const Lamb::SafePtr<LineCollisionComp>& lineCollisionComp);
	void Erase(const Lamb::SafePtr<LineCollisionComp>& lineCollisionComp);

	void Collision();

	void Clear();


private:
	std::unordered_set<Lamb::SafePtr<ObbComp>> obbComps_;
	std::unordered_set<Lamb::SafePtr<ObbPushComp>> obbPushComps_;
	std::unordered_set<Lamb::SafePtr<LineCollisionComp>> lineCollisionComps_;
};