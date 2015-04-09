#include "matrixloader.h"

#include <fstream>
#include <json/json.h>

using namespace std;

vector<vector<int>> MatrixLoader::getAll() const
{
	if (!loaded) {
		vector<vector<int>> observations;
		ifstream inSave{"observations.json", ifstream::binary};
		
		Json::Value root;
		
		if (inSave) {
			inSave >> root;
			for (auto game : root["games"]) {
				for (auto observation : game["observations"]) {
					vector<int> observationVec;
					for (auto result : observation) {
						observationVec.push_back(result.asInt());
					}
					observations.push_back(observationVec);
				}
			}
		}
		
		return observations;
	} else {
		return cache;
	}
}

void MatrixLoader::load()
{
	cache = getAll();
	loaded = true;
}
