#include "matrixprinter.h"

#include "matrixprovider.h"

#include <iostream>

using namespace std;

shared_ptr<MatrixProvider> MatrixPrinter::getObservation()
{
	return observation;
}

void MatrixPrinter::setObservation(shared_ptr<MatrixProvider> observation)
{
	this->observation = observation;
}

void MatrixPrinter::trigger()
{
	for (auto turn : observation->getVecVec()) {
		for (auto value : turn) {
			cout << value << ", ";
		}
		cout << endl;
	}
}
