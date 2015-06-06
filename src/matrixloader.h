#pragma once

#include <vector>
#include <string>

class MatrixLoader
{
public:
	MatrixLoader(std::string _path, std::string _name);
	std::vector<std::vector<std::vector<int>>> getAll() const;
	void load();
	
	
private:
	std::string path;
	std::string name;
	bool loaded = false;
	std::vector<std::vector<std::vector<int>>> cache;
};
