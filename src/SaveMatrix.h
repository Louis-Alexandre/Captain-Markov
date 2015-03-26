#pragma once

#include "event.h"

#include <memory>

class Observation;

class SaveMatrix : public Event
{
public:
    void trigger() override;
	
	void setPath(std::string path);
	std::string getPath();
	
	void setObservation(std::shared_ptr<Observation> observation);
	std::shared_ptr<Observation> getObservation() const;
	
private:
	std::string path;
	std::shared_ptr<Observation> observation;
};
