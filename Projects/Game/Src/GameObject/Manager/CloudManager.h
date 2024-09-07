#pragma once
#include "../Comp/CloudComp.h"
#include <unordered_set>
#include <memory>
#include "Utils/SafePtr.h"

class CloudManager
{
private:

	CloudManager() = default;
	CloudManager(const CloudManager&) = delete;
	CloudManager(CloudManager&&) = delete;
	CloudManager& operator=(const CloudManager&) = delete;
	CloudManager& operator=(CloudManager&&) = delete;

public:
	
	~CloudManager();

	static CloudManager* const GetInstance();

	static void Initialize();

	static void Finalize();

public:

	void Set(const Lamb::SafePtr<CloudComp>& cloudComp);
	void Erase(const Lamb::SafePtr<CloudComp>& cloudComp);

	void Clear();

	Lamb::SafePtr<CloudComp> GetDeadCloud();

	Lamb::SafePtr<CloudComp> GetAliveCloud(int32_t massX, int32_t massY);

private:

	static std::unique_ptr<CloudManager> instance_;

private:

	std::unordered_set<Lamb::SafePtr<CloudComp>> cloudComps_;

};

