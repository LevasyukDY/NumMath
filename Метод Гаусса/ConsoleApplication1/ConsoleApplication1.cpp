#include "pch.h"
#include <iostream>
#include <iomanip>

using namespace std;

/**
	Вывод системы уравнений
**/
void sysout(double a[5][5], double *y, int n)
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

/**
	Вычисления методом Гаусса
**/
double * gauss(double a[5][5], double *y, int n)
{
	double *x, max;
	int k, index;
	const double eps = 0.001; // точность
	x = new double[n];
	k = 0;
	while (k < n)
	{
		// Поиск строки с максимальным эл-м
		max = abs(a[k][k]);
		index = k;
		for (int i = k+1; i < n; i++)
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}

		// Перестановка строк
		if (max < eps)
		{
			// нет ненулевых диагональных эл-в
			cout << "Решение получить невозможно из-за нулевого столбца ";
			cout << index << " матрицы А" << endl;
			return 0;
		}

		for (int j = 0; j < n; j++)
		{
			double temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}

		double temp = y[k];
		y[k] = y[index];
		y[index] = temp;

		// Приведение к треугольному виду
		for (int i = k; i < n; i++)
		{
			double temp = a[i][k];
			if (abs(temp) < eps) 
				continue; // для нулевого кф пропустить
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			y[i] = y[i] / temp;
			if (i == k) 
				continue; // уравнение не вычитает само из себя
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j]; // обнуление эл-в ниже гл. диагонали
			y[i] = y[i] - y[k]; // обнуление столбца св. кф.
		}
		k++;
	}
	cout << endl;
	sysout(a, y, n);
	// Обратный подстановка
	for (k = n-1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++)
			y[i] = y[i] - a[i][k] * x[k];
	}
	return x;
}

int main()
{
	setlocale(0, "");
	const int n = 5;
	double a[n][n] = {{ 0.87,  0.25, -0.17, -0.88,  0.87},
				      {-0.53,  0.30,  0.70,  0.74,  0.77},
				      {-0.73, -0.64,  0.05,  0.93, -0.97},
				      { 0.28,  0.69, -0.52, -0.50, -0.05},
				      {-0.07, -0.80,  0.38, -0.64,  0.38}},
		   y[n]   =   { 0.29,  0.41, -0.72, -0.76,  0.48},
		  *x;

	system("cls");

	sysout(a, y, n);
	x = gauss(a, y, n);
	
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "x[" << i+1 << "] = ";
		if (x[i] >= 0)
			cout << " ";
		cout << x[i] << endl;
	}
	cin.get(); 
	cin.get();

	return 0;
}