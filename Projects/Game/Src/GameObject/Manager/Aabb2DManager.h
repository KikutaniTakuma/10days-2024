#pragma once
#include <memory>
#include <unordered_set>

#include "Utils/SafePtr.h"

#include "../Comp/Aabb2DComp.h"

class Aabb2DManager {
private:
	Aabb2DManager() = default;
	Aabb2DManager(const Aabb2DManager&) = delete;
	Aabb2DManager(Aabb2DManager&&) = delete;

	Aabb2DManager& operator=(const Aabb2DManager&) = delete;
	Aabb2DManager& operator=(Aabb2DManager&&) = delete;

public:
	~Aabb2DManager();

public:
	static Aabb2DManager* const GetInstance();

	static void Initialize();

	static void Finalize();

private:
	static std::unique_ptr<Aabb2DManager> instance_;

public:
	void Set(const Lamb::SafePtr<Aabb2DComp>& aabb2DComp);
	void Erase(const Lamb::SafePtr<Aabb2DComp>& aabb2DComp);

	void Collision();

	void Clear();


private:
	std::unordered_set<Lamb::SafePtr<Aabb2DComp>> aabb2DComps_;
};