#include "stdafx.h"
#include "math.h"
#include "DCTTransform.h"
// #include <iostream>
// #include <iomanip>

#define PI 3.14

using namespace std;

void DCT(double ** input, double ** output, int row, int col)
{
	// cout << "Test in DCT" << endl;
	double ALPHA, BETA;
	int u = 0;
	int v = 0;
	int i = 0;
	int j = 0;

	for (u = 0; u < row; u++)
	{
		for (v = 0; v < col; v++)
		{
			if (u == 0)
			{
				ALPHA = sqrt(1.0 / row);
			}
			else
			{
				ALPHA = sqrt(2.0 / row);
			}

			if (v == 0)
			{
				BETA = sqrt(1.0 / col);
			}
			else
			{
				BETA = sqrt(2.0 / col);
			}

			double tmp = 0.0;
			for (i = 0; i < row; i++)
			{
				for (j = 0; j < col; j++)
				{
					tmp += input[i][j] * cos((2 * i + 1)*u*PI / (2.0 * row)) * cos((2 * j + 1)*v*PI / (2.0 * col));
				}
			}
			// *((double*)output + col*u + v) = ALPHA * BETA * tmp;
			output[u][v] = ALPHA * BETA * tmp;
		}
	}

	// // cout << "The result of DCT:" << endl;
	// for (int m = 0; m < row; m++)
	// {
	// 	for (int n = 0; n < col; n++)
	// 	{
	// 		cout << setw(8) << *((double*)output + col*m + n) << " \t";
	// 	}
	// 	cout << endl;
	// }
}


void IDCT(double ** input, double ** output, int row, int col)
{
	// cout << "Test in IDCT" << endl;
	double ALPHA, BETA;
	int u = 0;
	int v = 0;
	int i = 0;
	int j = 0;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			double tmp = 0.0;
			for (u = 0; u < row; u++)
			{
				for (v = 0; v < col; v++)
				{
					if (u == 0)
					{
						ALPHA = sqrt(1.0 / row);
					}
					else
					{
						ALPHA = sqrt(2.0 / row);
					}
					if (v == 0)
					{
						BETA = sqrt(1.0 / col);
					}
					else
					{
						BETA = sqrt(2.0 / col);
					}
					tmp += ALPHA * BETA * input[u][v] * cos((2 * i + 1)*u*PI / (2.0 * row)) * cos((2 * j + 1)*v*PI / (2.0 * col));
				}
			}
			output[i][j] = tmp;
			// *((double*)output + col*i + j) = tmp;
		}
	}

	// cout << "The result of IDCT:" << endl;
	// for (int m = 0; m < row; m++)
	// {
	// 	for (int n = 0; n < col; n++)
	// 	{
	// 		cout << setw(8) << *((double*)output + col*m + n) << "\t";
	// 	}
	// 	cout << endl;
	// }
}
