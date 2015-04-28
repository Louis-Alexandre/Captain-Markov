#include "matrixprinter.h"

#include "operationVector.h"
#include "matrixprovider.h"

#include <iostream>

using namespace std;

MatrixPrinter::MatrixPrinter(shared_ptr< MatrixProvider > matrixProviderPtr) : matrixProvider{matrixProviderPtr}
{

}

void MatrixPrinter::trigger()
{
	showMat(matrixProvider->getMatrix());
}
