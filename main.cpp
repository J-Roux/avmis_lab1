/* 
 * File:   main.cpp
 * Author: pavel
 *
 * Created on аўторак, 26, студзеня 2016, 19.15
 */

#include <cstdlib>
#include <functional>
#include <iostream>
using namespace std;

template <size_t col, size_t row, class T>
class Matrix
{

	T data[col][row];	
public:

	Matrix(function<T()> init)
	{
		for(size_t i = 0; i < col; i++)
		{
			for(size_t j = 0; j < row; j++)
			{
				data[i][j] = init();
			}
		}
	}
	
	static Matrix construct(function<T()> init)
	{
		return Matrix(init);
	};
	
	Matrix() = default;
	Matrix(const Matrix&) = default;
	Matrix& operator = (const Matrix&) = default;
	
	inline T& operator () (size_t c, size_t r)
	{
		return data[c][r];
	}
	inline const T& operator () (size_t c, size_t r) const
	{
		return data[c][r];
	}
	
	
};



using Mat = Matrix<3, 3, double>;
using BMat = Matrix<1000, 1000, Mat>;



template<size_t col, size_t row, size_t col1, class T>
inline Matrix<col, col1, T>& operator * (const Matrix<col, row, T> &mat1, const Matrix<col1, row, T> &mat2 ) 
{
	auto temp = new Matrix<col, col1, T>();
	for(size_t i = 0; i < col; i++)
	{
		for(size_t j = 0; j < row ; j++)
		{
			for(size_t k = 0; k < col1; k++)
			{
				(*temp)(i, j) = (*temp)(i, j) + mat1(i, k) * mat2(k, j); 
			}
		}
	}
	return (*temp);
}

template<size_t col, size_t row, class T>
inline Matrix<col, row, T>& operator + (const Matrix<col, row, T> &mat1, const Matrix<col, row, T> &mat2)
{
	auto temp = new Matrix<col, row, T>();
	for(size_t i = 0; i < col; i++)
	{
		for(size_t j = 0; j < row ; j++)
		{
			(*temp)(i, j) = mat1(i, j) * mat2(i, j); 
		}
	}
	return (*temp);
}


/*
template<size_t col, size_t row, size_t col1, class T>
inline Matrix<col, col1, T>& operator * (const Matrix<col, row, T> *mat1, Matrix<col1, row, T> *mat2 ) 
{
	return (*mat1) * (*mat2);
}
*/


int main(int argc, char** argv)
{
	auto init = std::bind(Mat::construct, []{ return double(rand()) / RAND_MAX ; });
	auto mat1 = new BMat(init);
	auto mat2 = new BMat(init);
	auto mat = (*mat1) * (*mat2);
	
	for(size_t i = 0; i < 3; i++)
	{
		for(size_t j = 0; j < 3 ; j++)
			cout << (*mat1)(i, j)(i, j) << endl;
	}
	return 0;
}

