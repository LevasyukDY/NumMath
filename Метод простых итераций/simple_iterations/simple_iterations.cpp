#include <iostream>
#include <iomanip>

using namespace std;

void sysout(double a[5][5], double* y, int n)
{
	int i = 0, j = 0;
	
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (a[i][j] >= 0 && a[i][j] < 10)
				cout << "  ";

			if (a[i][j] >= 10 || a[i][j] < 0)
				cout << " ";

			cout << a[i][j] << "x" << j + 1;
			if (j < n - 1)
				cout << " + ";
		}
		cout << " = ";
		if (y[i] >= 0)
			cout << " ";
		cout << y[i] << endl;
	}
	return;
}

int main()
{
	setlocale(0, "");

	int i, j;
	const int n = 5;
	double a[n][n] = {{ 38,  6,  9, -2, -6 },
					  { -4, 36, -4, -6,  7 },
					  { -1,  1,  6, -1,  0 },
					  {  6, -4,  7, 23, -2 },
					  { -5,  7, -3,  8, 26 }},
			   b[n] = { 45, 58, 15, 60, 33 },
			   x[n], eps = 0.001, norma, 
			   xn[n] = { 0 };

	sysout(a, b, n);

	do {
		norma = 0.0;
		for (i = 0; i < n; i++) 
		{
			xn[i] = -b[i];
			for (j = 0; j < n; j++) 
			{
				if (i != j)
					xn[i] += a[i][j] * x[j];
			}
			xn[i] /= -a[i][i];
		}
		for (i = 0; i < n; i++) 
		{
			if (fabs(x[i] - xn[i]) > norma)
				norma = fabs(x[i] - xn[i]); //Вычисление нормы вектора
			x[i] = xn[i];
		}
	} while (norma > eps);

	cout << fixed;
	cout.precision(4);

	cout << endl;
	for (i = 0; i < n; i++) 
	{
		cout << "x" << i+1 << " = " << x[i] << endl;
	}

	cout << endl;
	system("pause");
	return 0;
}
