#pragma once

#include "event.h"

#include <memory>

class MatrixProvider;

class SaveMatrix : public Event
{
public:
	SaveMatrix(std::string _path, std::string _name);
    void trigger() override;
	
	void setPath(std::string path);
	std::string getPath();
	
	void setName(std::string name);
	std::string getName();
	
	void setMatrix(std::shared_ptr<MatrixProvider> matrix);
	std::shared_ptr<MatrixProvider> getMatrix() const;
	
private:
	std::string path;
	std::string name;
	std::shared_ptr<MatrixProvider> matrix;
};
