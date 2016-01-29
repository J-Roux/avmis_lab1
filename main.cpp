/* 
 * File:   main.cpp
 * Author: pavel
 *
 * Created on аўторак, 26, студзеня 2016, 19.15
 */

#include <cstdlib>
#include <functional>
#include <iostream>
#include <ctime>
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
	
	static Matrix* construct(function<T()> init)
	{
		return new Matrix(init);
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
using BMat = Matrix<1000, 1000, Mat*>;


/*
template<size_t col, size_t row, size_t col1, class T>
void mul (const Matrix<col, row, T> *mat1, const Matrix<col1, row, T> * mat2, Matrix<col, col1, T> * result ) 
{
	for(size_t i = 0; i < col; i++)
	{
		for(size_t j = 0; j < row ; j++)
		{
			for(size_t k = 0; k < col1; k++)
			{
				auto temp = new T();
				mul(mat1, mat2, temp);
				sum(result, temp);
				delete
				//(*temp)(i, j) = (*temp)(i, j) + mat1(i, k) * mat2(k, j); 
			}
		}
	}
}

template<size_t col, size_t row, class T>
inline Matrix<col, row, T>& operator + (const Matrix<col, row, T> &mat1, const Matrix<col, row, T> &mat2)
{
	auto temp = new Matrix<col, row, T>();
	for(size_t i = 0; i < col; i++)
	{
		for(size_t j = 0; j < row ; j++)
		{
			(*temp)(i, j) = mat1(i, j) + mat2(i, j); 
		}
	}
	return (*temp);
}


*/
#pragma pack(8);

int main(int argc, char** argv)
{
	/*
	auto init = std::bind(Mat::construct, []{ return double(rand()) / RAND_MAX ; });
	auto zero = std::bind(Mat::construct, []{ return 0; });
	const BMat * mat1 = new BMat(init);
	const BMat * mat2 = new BMat(init);
	BMat * result = new BMat(zero);
	auto start = std::clock();
	for(size_t i = 0; i < 1000; i++)
	{
		for(size_t j = 0; j < 1000; j++)
		{
			for(size_t k = 0; k < 1000; k++)
			{
				for(size_t i1 = 0; i1 < 3; i1++ )
				{
					for(size_t j1 = 0; j1 < 3; j1++ )
					{
						for(size_t k1 = 0; k1 < 3; k1++ )
						{
							(*(*result)(i, j))(i1, j1) += (*(*mat1)(i, k))( i1, k1) * (*(*mat2)(k, j))( k1, j1); 
						}
					}
				}
				// (*temp)(i, j) = (*temp)(i, j) + mat1(i, k) * mat2(k, j);
			}
		}
	}
	*/
	//auto start = std::clock();
	
	//double a[1000][1000][3][3] = {0};
//	double b[1000][1000][3][3] = {0};
//	double c[1000][1000][3][3] = {0};

	double**** __restrict_arr a = new double***[1000]; 
	double**** __restrict_arr b = new double***[1000];
	double**** __restrict_arr c = new double***[1000];
	
	for(int i = 0; i < 1000; i++)
	{
		a[i] = new double**[1000];
		b[i] = new double**[1000];
		c[i] = new double**[1000];
		for(int j = 0; j < 1000; j++)
		{
			a[i][j] = new double*[3];
			b[i][j] = new double*[3];
			c[i][j] = new double*[3];
			for(int k = 0; k < 3; k++)
			{
				a[i][j][k] = new double[3];
				b[i][j][k] = new double[3];
				c[i][j][k] = new double[3];
				for(int l = 0; l < 3; l++)
				{
					a[i][j][k][l] = 0;
					b[i][j][k][l] = double(rand());
					c[i][j][k][l] = double(rand());
				}
			}			
		}
	}
	/*
	for(int i1 = 0; i1 < 1000; i1++)
	{
		for(int j1 = 0; j1 < 1000; j1++)
		{
			for(int k1 = 0; k1 < 1000; k1++)
			{
				for(int i = 0; i < 3; i++)
				{
					for(int j = 0; j < 3; j++)
					{
						for(int k = 0; k < 3; k++)
						{
							c[i1][j1][i][j] = double(rand());
						}
					}
				}
			}
		}
	}*/
	double acc = 0;
	for(int i1 = 0; i1 < 1000; i1++)
	{
		for(int j1 = 0; j1 < 1000; j1++)
		{
			for(int k1 = 0; k1 < 1000; k1++)
			{
				for(int i = 0; i < 3; i++)
				{
					for(int j = 0; j < 3; j++)
					{
						for(int k = 0; k < 3; k++)
						{
							acc = b[k1][j1][k][j] * c[j1][k1][k][j];
							a[i1][j1][i][j] += acc;
						}
						acc = 0;
					}
				}
			}
		}
	}
	cout << a[0][0][0][0] << endl;
	cout << a[0][0][0][0] << endl;
	cout << a[0][3][1][0] << endl;
	cout << a[0][0][2][0] << endl;
	//cout << std::clock() - start << endl;
	return 0;
}

