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
boost::numeric::ublas::matrix<T> operator+(boost::numeric::ublas::matrix<T> mat, double scalar)
{
    for ( int l = 0 ; l < mat.size1(); ++l ) {
        for ( int c = 0 ; c < mat.size2(); ++c) {
			mat(l, c) += scalar;
		}
	}
	return mat;
}

template<typename T>
boost::numeric::ublas::matrix<T> operator-(boost::numeric::ublas::matrix<T> mat, double scalar) {
	return mat + -1*scalar;
}

template<typename T>
boost::numeric::ublas::matrix<T> expMat(boost::numeric::ublas::matrix<T> mat)
{
	for ( int l = 0 ; l < mat.size1(); ++l ) {
        for ( int c = 0 ; c < mat.size2(); ++c) {
			mat(l, c) = std::exp(mat(l, c));
		}
	}
	return mat;
}

template<typename T>
T sum(const std::vector<T>& vec)
{
	return std::accumulate(vec.cbegin(), vec.cend(), 0);
}

template<typename T>
T sum(boost::numeric::ublas::matrix<T>& mat)
{
    T total = 0;

    for ( int l = 0 ; l < mat.size1(); ++l ) {
        for ( int c = 0 ; c < mat.size2(); ++c) {
			total += mat(l, c);
        }
    }
    return total;
}

template<typename T>
T sum(std::vector<T>&& vec)
{
	return sum(vec);
}

template<typename T>
T sum(boost::numeric::ublas::matrix<T>&& mat)
{
    T total = 0;

    for ( int l = 0 ; l < mat.size1(); ++l ) {
        for ( int c = 0 ; c < mat.size2(); ++c) {
			total += mat(l, c);
        }
    }
    return total;
}

template<typename T>
boost::numeric::ublas::matrix<T> ligne(boost::numeric::ublas::matrix<T> A, int laligne) {

    boost::numeric::ublas::matrix<T> result(1,A.size2());

	for (int i = 0; i < A.size2(); ++i) {
		result(0,i) = A(laligne,i);
	}
	
	return result;
}

template<typename T>
boost::numeric::ublas::matrix<T> col(boost::numeric::ublas::matrix<T> A, int lacol) {

	boost::numeric::ublas::matrix<T> result(A.size1(),1);

	for (int i = 0; i < A.size1(); ++i) {
		result(i,0) = A(i,lacol);
	}
	return result;
}

template<typename T>
T getMax(boost::numeric::ublas::matrix<T> A) {

    T max = A(0,0);

    for ( int l = 0 ; l < A.size1(); ++l ) {
        for ( int c = 0 ; c < A.size2(); ++c) {
			max = std::max(A(l,c), max);
        }
    }
    return max;
}

template<typename T>
std::vector<T> expVec(std::vector<T> vec)
{
	for (auto& element : vec) {
		element = std::exp(element);
	}
	return vec;
}
