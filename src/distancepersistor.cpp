#include "distancepersistor.h"

#include "distanceaccumulator.h"

#include <json/json.h>
#include <fstream>

using namespace std;

DistancePersistor::DistancePersistor(shared_ptr< DistanceAccumulator > _distanceAccumulator) : distanceAccumulator{_distanceAccumulator} {}

void DistancePersistor::trigger()
{
	{
		ifstream inSave{"data/distances.json", ifstream::binary};
		Json::Value root;
		
		if (inSave) {
				inSave >> root;
		} else {
			root["games"] = Json::arrayValue;
		}
		
		Json::Value game = Json::objectValue;
		game["distances"] = Json::arrayValue;
		
		for (auto distances : distanceAccumulator->getDistances()) {
			game["distances"].append(distances);
		}
		
		root["games"].append(game);
		ofstream outSave{"data/distances.json", ifstream::binary | ofstream::trunc};
		
		Json::FastWriter writer;
		outSave << writer.write(root);
	}
	
	{
		ifstream inSave{"data/distances_avg.json", ifstream::binary};
		Json::Value root;
		
		if (inSave) {
				inSave >> root;
		} else {
			root["games"] = Json::arrayValue;
		}
		
		Json::Value game = Json::intValue;
		
		double avg;
		for (auto distance : distanceAccumulator->getDistances()) {
			avg += distance;
		}
		game = avg / distanceAccumulator->getDistances().size();
		
		root["games"].append(game);
		ofstream outSave{"data/distances_avg.json", ifstream::binary | ofstream::trunc};
		
		Json::FastWriter writer;
		outSave << writer.write(root);
	}
	
	
	distanceAccumulator->reset();
}
