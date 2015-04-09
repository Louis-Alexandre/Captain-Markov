#pragma once

#include <vector>

class MatrixLoader
{
public:
	std::vector<std::vector<std::vector<int>>> getAll() const;
	void load();
	
private:
	bool loaded = false;
	std::vector<std::vector<std::vector<int>>> cache;
};
