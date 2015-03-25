#pragma once

class MapInfo
{
public:
	virtual unsigned int getTileHeight() = 0;
	virtual unsigned int getTileWidth() = 0;
	virtual unsigned int getHeight() = 0;
	virtual unsigned int getWidth() = 0;
};
