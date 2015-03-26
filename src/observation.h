#pragma once

#include "event.h"

#include <memory>
#include <vector>
#include <set>

class Map;
class Entity;

class Observation : public Event
{
public:
	std::shared_ptr<Map> getMap() const;
	void setMap(std::weak_ptr<Map> map);
	
    void trigger() override;
	
	void setSubject(std::shared_ptr<Entity> subject);
	std::shared_ptr<Entity> getSubject() const;
	
	std::vector<std::vector<int>> getObservations() const;
	
private:
	std::vector<std::vector<int>> observations;
	std::shared_ptr<Entity> subject;
	std::weak_ptr<Map> mapRef;
};
