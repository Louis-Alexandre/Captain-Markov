#include "concretemapinfo.h"

#include "Map.h"

using namespace std;

ConcreteMapInfo::ConcreteMapInfo(shared_ptr<Map> map) : map{map}
{

}

uint ConcreteMapInfo::getHeight()
{
	return map->getHeight();
}

uint ConcreteMapInfo::getTileHeight()
{
	return map->getTileHeight();
}

uint ConcreteMapInfo::getTileWidth()
{
	return map->getTileWidth();
}

uint ConcreteMapInfo::getWidth()
{
	return map->getWidth();
}
