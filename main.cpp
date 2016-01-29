/*
 * File:   main.cpp
 * Author: pavel
 *
 * Created on аўторак, 26, студзеня 2016, 19.15
 */

#include <stdio.h>
#include <stdlib.h>

#pragma pack(8)


int main(int argc, char** argv)
{


	double**** __restrict a = (double****)calloc(1000, sizeof(double***));
	double**** __restrict b = (double****)calloc(1000, sizeof(double***));
	double**** __restrict c = (double****)calloc(1000, sizeof(double***));



	for(int i = 0; i < 1000; i++)
	{
		a[i] = (double***)calloc(1000, sizeof(double**));
		b[i] = (double***)calloc(1000, sizeof(double**));
		c[i] = (double***)calloc(1000, sizeof(double**));
		for(int j = 0; j < 1000; j++)
		{
			a[i][j] = (double**)calloc(3, sizeof(double*));
			b[i][j] = (double**)calloc(3, sizeof(double*));
			c[i][j] = (double**)calloc(3, sizeof(double*));
			for(int k = 0; k < 3; k++)
			{
				a[i][j][k] = (double*)calloc(3, sizeof(double));
				b[i][j][k] = (double*)calloc(3, sizeof(double));
				c[i][j][k] = (double*)calloc(3, sizeof(double));
				for(int l = 0; l < 3; l++)
				{
					a[i][j][k][l] = 0;
					b[i][j][k][l] = double(rand());
					c[i][j][k][l] = double(rand());
				}
			}
		}
	}

	double**** x = (double****)__builtin_assume_aligned(a, 8);
	double**** y = (double****)__builtin_assume_aligned(b, 8);
	double**** z = (double****)__builtin_assume_aligned(c, 8);

	double *acc = (double *)calloc(3, sizeof(double));
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
								z[i1][j1][i][j] += x[k1][j1][k][j] * y[j1][k1][k][j];
						}

					}
				}
			}
		}
	}
    printf("%f", z[0][0][0][0]);
	//cout << std::clock() - start << endl;
	return 0;
}

