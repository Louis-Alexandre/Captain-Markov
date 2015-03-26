#pragma once

#include "goal.h"
#include "SFML/Graphics.hpp"
#include "Entity/Entity.h"
#include <memory>

class Entity;
class Map;

struct CaptainFoundPlayer : Goal
{
public:
	CaptainFoundPlayer();
	bool check() override;
	void setCaptain(std::shared_ptr<Entity> captain);
	std::shared_ptr<Entity> getCaptain() const;
	void setMatelot(std::shared_ptr<Entity> matelot);
	std::shared_ptr<Entity> getMatelot() const;
	void setMap(std::weak_ptr<Map> map);
	std::shared_ptr<Map> getMap() const;
	
	
private:
	std::shared_ptr<Entity> _captain;
	std::shared_ptr<Entity> _matelot;
	std::weak_ptr<Map> _mapRef;
	
};
