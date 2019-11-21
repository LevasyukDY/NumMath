#include <iostream>
#include <iomanip>

using namespace std;

void sysout(double a[5][5], double* y, int n)
{
	int i = 0, j = 0;
	cout << fixed;
	cout.precision(2);
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (a[i][j] >= 0)
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
	const unsigned n = 5;

	double s; // сумматор
	double a[n][n] = {{ 0.87,  0.25, -0.17, -0.88,  0.87},
					  {-0.53,  0.30,  0.70,  0.74,  0.77},
					  {-0.73, -0.64,  0.05,  0.93, -0.97},
					  { 0.28,  0.69, -0.52, -0.50, -0.05},
					  {-0.07, -0.80,  0.38, -0.64,  0.38}},
		       c[n] = { 0.29,  0.41, -0.72, -0.76,  0.48},
			   b[n][n], t[n][n], x[n], y[n];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			b[i][j] = 0;
			t[i][j] = 0;
		}
		x[i] = 0;
		y[i] = 0;
	}

	//cout << endl;
	sysout(a, c, n);
	cout << endl;

	// инициализация столбца матрицы b и строки матрицы t
	for (int i = 0; i < n; i++) {
		b[i][0] = a[i][0];
		t[0][i] = a[0][i] / b[0][0];
	}
	//sysout(b, c, n);
	//cout << endl;
	//sysout(t, c, n);
	//cout << endl;

	// вычисления
	for (int k = 1; k < n; k++) {
		for (int i = k; i < n; i++) {
			s = 0;
			for (int m = 0; m < k; m++)
				s = s + b[i][m] * t[m][k];
			b[i][k] = a[i][k] - s;
			for (int j = k; j < n; j++) {
				s = 0;
				for (int m = 0; m < k; m++)
					s = s + b[k][m] * t[m][j];
				t[k][j] = (a[k][j] - s) / b[k][k];
			}
		}
	}

	//sysout(b, c, n);
	//cout << endl;
	//sysout(t, c, n);
	//cout << endl;

	// находим y1
	y[0] = c[0] / b[0][0];

	// находим остальные y
	for (int k = 1; k < n; k++) {
		s = 0;
		for (int i = 0; i < k; i++) {
			s += b[k][i] * y[i];
		}
		y[k] = (c[k] - s) / b[k][k];
	}

	// находим последний x (с конца в начало)
	x[n - 1] = y[n - 1];
	for (int k = n - 2; k >= 0; k--) {
		s = 0;
		for (int i = k + 1; i < n; i++)
			s += t[k][i] * x[i];
		x[k] = y[k] - s;
	}

	for (int i = 0; i < n; i++)//вывод результата
		cout << "x" << i + 1 << " = " << x[i] << "\n";

	system("pause");
	return 0;
}
