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
};


using Mat = Matrix<3, 3, int>;
//using BMat = Matrix<1000, 1000, Mat>;




Mat bar(){ return Mat(rand); }

int main(int argc, char** argv)
{
	auto f = std::bind(&Mat::construct, rand);
	auto mat = new Matrix<1000, 1000, Mat>(&bar);
	return 0;
}

