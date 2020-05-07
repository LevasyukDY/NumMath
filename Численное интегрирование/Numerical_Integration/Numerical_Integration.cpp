#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;

// Первая функция
float f1(float x)
{
	return 1 / sqrt(pow(x, 2) + 0.5);
}

// Вторая функция
float f2(float x)
{
	return cos(x) / (x + 2);
}

// Вторая производная первой функции
float f1_xx(float x)
{
	return (2 * (pow(x, 2) - 0.25)) / pow(0.5 + pow(x, 2), 5 / 2);
}


float max_f1_xx(float a, float b, float eps)
{
	float k = ceil((b - a) / eps),
		d = (b - a) / k;
	vector<float> vec;

	for (int i = 0; i < k + 1; i++)
		vec.push_back(f1_xx(a + i * d));

	return *max_element(vec.begin(), vec.end());
}


float trapezoid_method(float a, float b, float eps, float max)
{
	int n = sqrt(max * pow(b - a, 3) / (12 * eps));
	float h = (b - a) / n,
		w = 0, x;

	for (int k = 1; k <= n - 1; k++)
	{
		x = a + k * h;
		w += f1(x);
	}
	w = (2 * w + f1(a) + f1(b)) * h / 2;

	return w;
}


float simpson_method(float a, float b, float m)
{
	float n = 2 * m,
		h = (b - a) / n,
		s = 0,
		s1 = 0,
		s2 = 0, x;

	for (int k = 1; k <= m; k++)
	{
		x = a + (2 * k - 1) * h;
		s1 += f2(x);
	}

	for (int k = 1; k <= m - 1; k++)
	{
		x = a + 2 * k * h;
		s2 += f2(x);
	}

	s = (4 * s1 + 2 * s2 + f2(a) + f2(b)) * h / 3;

	return s;
}


int main()
{
	setlocale(0,"");

	float a = 1.2f;
	float b = 2.4f;
	const float eps = 0.001f;
	float max = 9;

	cout << "Первый интеграл = " << trapezoid_method(a, b, eps, max) << endl;

	float a1 = 0.4f;
	float b1 = 1.2f;
	float m = 8;

	float I1 = simpson_method(a1, b1, m);
	m++;
	float I2 = simpson_method(a1, b1, m);

	// Оценка погрешности
	while (fabs(I1 - I2) > eps)
	{
		I1 = I2;
		m++;
		I2 = simpson_method(a1, b1, m);
	}

	cout << "Второй интеграл = " << I2 << endl << endl;

	system("pause");
	return 0;
}