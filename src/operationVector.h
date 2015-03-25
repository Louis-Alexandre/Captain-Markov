#pragma once

#include <numeric>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

template<typename T>
std::vector<T> scalarMultiplication(std::vector<T> vec, double scalar)
{
	for (auto& element : vec) {
		element *= scalar;
	}
	return vec;
}

template<typename T>
T sum(const std::vector<T>& vec)
{
	return std::accumulate(vec.cbegin(), vec.cend(), T());
}

template<typename T>
T sum(std::vector<T>&& vec)
{
	return sum(vec);
}

template<typename T>
T sum(boost::numeric::ublas::matrix<T>& mat)
{
	T total = T();
	for (int i=0 ; i<mat.size1() ; ++i) {
		for (int j=0 ; j<mat.size2() ; ++j) {
			total += mat(i, j);
		}
	}
	return total;
}

template<typename T>
void printMat(boost::numeric::ublas::matrix<T>& mat)
{
	for (int i=0 ; i<mat.size1() ; ++i) {
		for (int j=0 ; j<mat.size2() ; ++j) {
			std::cout <<  mat(i, j) << ' ';
		}
		std::cout << std::endl;
	}
}