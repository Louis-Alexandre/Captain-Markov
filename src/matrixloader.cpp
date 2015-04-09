#include "matrixloader.h"

#include <fstream>
#include <json/json.h>

using namespace std;

vector<vector<vector<int>>> MatrixLoader::getAll() const
{
	if (!loaded) {
		vector<vector<vector<int>>> observations;
		ifstream inSave{"observations.json", ifstream::binary};
		
		Json::Value root;
		
		if (inSave) {
			inSave >> root;
			for (auto game : root["games"]) {
				vector<vector<int>> gameVec;
				for (auto observation : game["observations"]) {
					vector<int> observationVec;
					for (auto result : observation) {
						observationVec.push_back(result.asInt());
					}
					gameVec.push_back(observationVec);
				}
				observations.push_back(gameVec);
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
