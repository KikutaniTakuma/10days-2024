#include "MapChipManager.h"
#include "../Comp/CsvDataComp.h"

std::unique_ptr<MapChipManager> MapChipManager::instance_;

MapChipManager* const MapChipManager::GetInstance()
{
	return instance_.get();
}

void MapChipManager::Initialize()
{

	if (instance_) {
		return;
	}

	instance_.reset(new MapChipManager());

}

void MapChipManager::Finalize()
{
	instance_.reset();
}

MapChipManager::~MapChipManager()
{
	
}


