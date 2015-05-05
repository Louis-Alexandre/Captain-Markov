#include "SaveMatrix.h"
#include "observation.h"

#include <json/json.h>
#include <iostream>
#include <fstream>

using namespace std;

void SaveMatrix::trigger()
{
	if (observation->getObservations().size() > 4) {
		ifstream inSave{"observations.json", ifstream::binary};
		Json::Value root;
		
		if (inSave) {
				inSave >> root;
		} else {
			root["games"] = Json::arrayValue;
		}
		
		Json::Value game = Json::objectValue;
		game["observations"] = Json::arrayValue;
		
		for (auto turn : observation->getObservations()) {
			Json::Value turnValue = Json::arrayValue;
			
			for (auto value : turn) {
				turnValue.append(value);
			}
			game["observations"].append(turnValue);
		}
		
		root["games"].append(game);
		ofstream outSave{"observations.json", ifstream::binary | ofstream::trunc};
		
		Json::FastWriter writer;
		outSave << writer.write(root);
	}
	observation->reset();
}

shared_ptr<Observation> SaveMatrix::getObservation() const
{
	return observation;
}

void SaveMatrix::setObservation(shared_ptr<Observation> observation)
{
	this->observation = observation;
}
