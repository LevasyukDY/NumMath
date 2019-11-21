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


bool check_eps(double x_new[5], double x_old[5]) 
{
	float eps = 0.001;
	for (unsigned i = 0; i < 5; i++)
	{
		if (fabs(x_old[i] - x_new[i]) > eps)
			return 0;
	}
	return 1;
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
		x_old[5] = { 0 }, 
		x_new[5] = { 0 }, 
		Sum = 0;

	sysout(a, b, n);


	do {
		for (i = 0; i < 5; i++)
		{
			x_old[i] = x_new[i];
		}
		for (i = 0; i < 5; i++)
		{
			Sum = b[i];
			for (j = 0; j < 5; j++)
			{
				if (j == i) 
					continue;
				//находим новые значения x
				Sum -= a[i][j] * x_new[j];
			}
			x_new[i] = Sum / a[i][i];
		}

	} while (!check_eps(x_old, x_new));


	cout << fixed;
	cout.precision(4);

	cout << endl;
	for (i = 0; i < n; i++)
	{
		cout << "x" << i + 1 << " = " << x_new[i] << endl;
	}

	cout << endl;
	system("pause");
	return 0;
}
