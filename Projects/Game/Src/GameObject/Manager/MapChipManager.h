#pragma once
#include "../Comp/CloudComp.h"
#include <unordered_set>
#include <memory>
#include "Utils/SafePtr.h"

class MapChipManager
{
private:

	MapChipManager() = default;
	MapChipManager(const MapChipManager&) = delete;
	MapChipManager(MapChipManager&&) = delete;
	MapChipManager& operator=(const MapChipManager&) = delete;
	MapChipManager& operator=(MapChipManager&&) = delete;

public:

	~MapChipManager();

	static MapChipManager* const GetInstance();

	static void Initialize();

	static void Finalize();

public:

	

private:

	static std::unique_ptr<MapChipManager> instance_;

private:

};

