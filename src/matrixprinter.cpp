#include "matrixprinter.h"

#include "observation.h"

#include <iostream>

using namespace std;

shared_ptr< Observation > MatrixPrinter::getObservation()
{
	return observation;
}

void MatrixPrinter::setObservation(shared_ptr< Observation > observation)
{
	this->observation = observation;
}

void MatrixPrinter::trigger()
{
	for (auto turn : observation->getObservations()) {
		for (auto value : turn) {
			cout << value << ", ";
		}
		cout << endl;
	}
}
