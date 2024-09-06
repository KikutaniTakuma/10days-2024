#pragma once
#include <memory>
#include <unordered_set>

#include "Utils/SafePtr.h"

#include "../Comp/ObbPushComp.h"

class ObbManager {
private:
	ObbManager() = default;
	ObbManager(const ObbManager&) = delete;
	ObbManager(ObbManager&&) = delete;

	ObbManager& operator=(const ObbManager&) = delete;
	ObbManager& operator=(ObbManager&&) = delete;

public:
	~ObbManager();

public:
	static ObbManager* const GetInstance();

	static void Initialize();

	static void Finalize();

private:
	static std::unique_ptr<ObbManager> instance_;

public:
	void Set(const Lamb::SafePtr<ObbComp>& obbComp);
	void Set(const Lamb::SafePtr<ObbPushComp>& obbPushComp);
	void Erase(const Lamb::SafePtr<ObbComp>& obbComp);
	void Erase(const Lamb::SafePtr<ObbPushComp>& obbPushComp);

	void Collision();

	void Clear();


private:
	std::unordered_set<Lamb::SafePtr<ObbComp>> obbComps_;
	std::unordered_set<Lamb::SafePtr<ObbPushComp>> obbPushComps_;
};