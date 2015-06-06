#include "SaveMatrix.h"
#include "observation.h"

#include <json/json.h>
#include <iostream>
#include <fstream>

using namespace std;

SaveMatrix::SaveMatrix(string _path, string _name) : path{_path}, name{_name} {}

void SaveMatrix::trigger()
{
	if (matrix->getVecVec().size() > 4) {
		ifstream inSave{path, ifstream::binary};
		Json::Value root;
		
		if (inSave) {
				inSave >> root;
		} else {
			root["games"] = Json::arrayValue;
		}
		
		Json::Value game = Json::objectValue;
		game[name] = Json::arrayValue;
		
		for (auto turn : matrix->getVecVec()) {
			Json::Value turnValue = Json::arrayValue;
			
			for (auto value : turn) {
				turnValue.append(value);
			}
			game[name].append(turnValue);
		}
		
		root["games"].append(game);
		ofstream outSave{path, ifstream::binary | ofstream::trunc};
		
		Json::FastWriter writer;
		outSave << writer.write(root);
	}
	matrix->reset();
}

shared_ptr<MatrixProvider> SaveMatrix::getMatrix() const
{
	return matrix;
}

string SaveMatrix::getName()
{
	return name;
}

string SaveMatrix::getPath()
{
	return path;
}


void SaveMatrix::setMatrix(shared_ptr<MatrixProvider> matrix)
{
	this->matrix = matrix;
}

void SaveMatrix::setName(string name)
{
	this->name = name;
}

void SaveMatrix::setPath(string path)
{
	this->path = path;
}

