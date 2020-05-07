#include <iostream>
#include <math.h>

using namespace std;

const float eps = 0.001;

float f(float x)
{
	return pow(1.3, sqrt(x*x - x + 2));
}

void SvenMethod(float &a, float &b, float x0, float d)
{
	float xN;
	float xC = x0;
	float xL = x0 - d;
	float xR = x0 + d;

	while (!((f(xL) > f(xC)) && (f(xR) > f(xC))))
	{
		if ((f(xL) > f(xC)) && (f(xC) > f(xR)))
		{
			xN = xR + 2 * d;
			xL = xC;
			xC = xR;
			xR = xN;
		} else {
			if ((f(xL) < f(xC)) && (f(xC) < f(xR)))
			{
				xN = xL - 2 * d;
				xR = xC;
				xC = xL;
				xL = xN;
			}
		}
		d = 2 * d;
	}
	a = xL;
	b = xR;
}

float PassiveSearch(const float& a, const float& b)
{
	unsigned k = 1;

	float min = f(a),
		n = (b - a) / (((b - a) / eps) + 1),
		xK = a + (k * n);

	while (f(xK) < min)
	{
		min = f(xK);
		k++;
		xK = a + (k * n);
	}
	return xK;
}

float Halving(float a, float b) 
{
	float x1, x2, x3, x = 0;

	while (b - a > 2 * eps) 
	{
		x1 = (3 * a + b) / 4;
		x2 = (a + b) / 2;
		x3 = (a + 3 * b) / 4;
		if ((f(x1) < f(x2)) && (f(x2) < f(x3)))
			b = x2;
		else
			if ((f(x1) > f(x2)) && (f(x2) > f(x3)))
				a = x2;
			else
			{
				a = x1;
				b = x3;
			}
		x = (a + b) / 2;
	}
	return x;
}

float Golden(float a, float b) 
{
	float phi = (sqrt(5) - 1) / 2,
		x1, x2, x_min = 0;
	while (b - a > 2 * eps) 
	{
		x1 = phi * a + (1 - phi) * b;
		x2 = (1 - phi) * a + phi * b;
		if (f(x1) < f(x2))
			b = x2;
		else
			a = x1;
		x_min = (a + b) / 2;
	}
	return x_min;
}


int main()
{
	float a = 0, b = 0;

	SvenMethod(a, b, -1, 0.01);

	cout << "a = " << a << endl;
	cout << "b = " << b << endl << endl;

	cout << PassiveSearch(a, b) << endl;

	cout << Halving(a, b) << endl;

	cout << Golden(a, b) << endl;

	system("pause");
	return 0;
}