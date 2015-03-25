#pragma once

#include "mapinfo.h"

#include <memory>

class Map;

class ConcreteMapInfo : public MapInfo
{
public:
	ConcreteMapInfo(std::shared_ptr<Map> map = nullptr);
	
	uint getTileHeight() override;
	uint getTileWidth() override;
	uint getHeight() override;
	uint getWidth() override;
	
private:
	std::shared_ptr<Map> map;
};
