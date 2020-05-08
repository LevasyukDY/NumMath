#include <iostream>
#include <vector>

using namespace std;

float f(float x, float y)
{
	return (5 * x * x - 2) * cos(y);
}

void print(vector<float> y)
{
	for (int i = 0; i < y.size(); i++)
	{
		cout << y[i] << " ";
	}
	cout << "\n\n";
}

vector<float> RungeKutta(vector<float> x, vector<float> y, int n, float h)
{
	float a, b, c, d;
	for (size_t k = 0; k < n; k++)
	{
		a = h * f(x[k], y[k]);
		b = h * f(x[k] + h / 2, y[k] + a / 2);
		c = h * f(x[k] + h / 2, y[k] + b / 2);
		d = h * f(x[k] + h, y[k] + c);
		y[k + 1] = y[k] + (a + 2 * b + 2 * c + d) / 6;
	}
	return y;
}

vector<float> Miln(vector<float> x, int n, float h)
{
	vector<float> y, y1, y2;
	y.resize(11);
	y1.resize(11);
	y2.resize(11);
	const float eps = 0.001;
	float eps_k = 0;
	y[0] = 1;
	y = RungeKutta(x, y, 3, h); // находим начальный отрезок
	int k = 4;

	while (k <= n)
	{
		y1[k] = y[k - 4] + (4 * h) / 3 * (2 * f(x[k - 3], y[k - 3])
			- f(x[k - 2], y[k - 2]) + 2 * f(x[k - 1], y[k - 1]));
		y2[k] = y[k - 2] + (h / 3) * (f(x[k - 2], y[k - 2])
			+ 4 * f(x[k - 1], y[k - 1]) + f(x[k], y1[k]));
		float t = (float)1 / 29;
		eps_k = t * abs(y2[k] - y1[k]);

		if (eps_k < eps)
		{
			y[k] = y2[k];
			k++;
		}
		else
		{
			h = h / 2;
			y = RungeKutta(x, y, 3, h);
			k = 4;
		}
	}
	return y;
}

int main()
{
	setlocale(0, "");

	int n = 10;
	vector<float> x, y;

	y.resize(11);
	x.resize(11);

	y[0] = 1;
	float h = 0.1;

	x[0] = 0;
	for (int i = 1; i < n; i++)
	{
		x[i] = x[i - 1] + h;
	}

	// Метод Эйлера
	for (int k = 0; k < n; k++)
	{
		y[k + 1] = y[k] + h * f(x[k], y[k]);
	}

	print(y);

	// Модифицированный метод Эйлера
	for (int k = 0; k < n; k++)
	{
		y[k + 1] = y[k] + h * f(x[k] + h / 2, y[k] + h / 2 * f(x[k], y[k]));
	}

	print(y);

	// Метод Рунге-Кутта
	y = RungeKutta(x, y, n, h);

	print(y);

	// Метод Адамса 1 порядка
	for (int k = 3; k < n; k++)
	{
		y[k + 1] = y[k] + h / 2 * (3 * f(x[k], y[k]) - f(x[k - 1], y[k - 1]));
	}

	print(y);

	float t;
	// Метод Адамса 2 порядка
	for (int k = 3; k < n; k++)
	{
		t = 23 * f(x[k], y[k]) - 16 * f(x[k - 1], y[k - 1]) + 5 * f(x[k - 2], y[k - 2]);
		y[k + 1] = y[k] + h / 12 * t;
	}

	print(y);

	// Метод Адамса 3 порядка
	for (int k = 3; k < n; k++)
	{
		t = 55 * f(x[k], y[k]) - 59 * f(x[k - 1], y[k - 1]) + 37 * f(x[k - 2], y[k - 2])
			- 9 * f(x[k - 3], y[k - 3]);
		y[k + 1] = y[k] + h / 24 * t;
	}

	print(y);

	// Метод Милна
	y = Miln(x, n, h);

	print(y);

	system("pause");
	return 0;
}
