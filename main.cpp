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
	
public:
	T data[col][row];
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
	
	
};


using Mat = Matrix<3, 3, double>;
using BMat = Matrix<1000, 1000, Mat>;




Mat bar(){ return Mat(rand); }

int main(int argc, char** argv)
{
	auto init = std::bind(&Mat::construct, []{ return double(rand()) / RAND_MAX ; });
	auto mat = new BMat(init);
	return 0;
}

