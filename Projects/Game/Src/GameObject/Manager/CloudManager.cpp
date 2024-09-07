#include "CloudManager.h"

std::unique_ptr<CloudManager> CloudManager::instance_;

CloudManager* const CloudManager::GetInstance()
{
	return instance_.get();
}

void CloudManager::Initialize()
{

	if (instance_) {
		return;
	}

	instance_.reset(new CloudManager());

}

void CloudManager::Finalize()
{
	instance_.reset();
}

void CloudManager::Set(const Lamb::SafePtr<CloudComp>& cloudComp)
{

	if (not cloudComps_.contains(cloudComp)) {
		cloudComps_.insert(cloudComp);
	}

}

void CloudManager::Erase(const Lamb::SafePtr<CloudComp>& cloudComp)
{

	if (cloudComps_.contains(cloudComp)) {
		cloudComps_.erase(cloudComp);
	}

}

void CloudManager::Clear()
{
	cloudComps_.clear();
}

Lamb::SafePtr<CloudComp> CloudManager::GetDeadCloud()
{

	for (auto cloud = cloudComps_.begin(); cloud != cloudComps_.end(); cloud++) {

		if (not (*cloud)->GetIsActive()) {
			return (*cloud);
		}

	}

	return nullptr;
}

Lamb::SafePtr<CloudComp> CloudManager::GetAliveCloud(int32_t massX, int32_t massY)
{
	
	for (auto cloud = cloudComps_.begin(); cloud != cloudComps_.end(); cloud++) {

		//指定したマスの雲が生存している場合それを返す
		if ((*cloud)->GetMassX() == massX and (*cloud)->GetMassY() == massY) {

			if ((*cloud)->GetIsActive()) {
				return (*cloud);
			}

			return nullptr;

		}

	}

	return nullptr;

}

CloudManager::~CloudManager()
{
	cloudComps_.clear();
}


