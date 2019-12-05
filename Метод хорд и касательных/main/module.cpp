#include "module.h"

// функция под буквой (а)
double f1(double x)
{
	return 7 * x + pow(5, x) - 2;
}

// производная функции (а) первого порядка
double f1_1(double x)
{
	return pow(5, x) * log(5) + 7;
}

// производная функции (а) второго порядка
double f1_2(double x)
{
	return pow(5, x) * pow(log(5), 2);
}

// функция под буквой (б)
double f2(double x)
{
	return -1 * pow(x, 3) - 3 * pow(x, 2) - 5 * x + 4;
}

// производная функции (б) первого порядка
double f2_1(double x)
{
	return -3 * pow(x, 2) - 6 * x - 5;
}

// производная функции (б) второго порядка
double f2_2(double x)
{
	return -6 * x - 6;
}

// вычисления
double calc(double a, double b, unsigned n, unsigned &it)
{
	double e = 0.0001, x = 0, c = 0, d = 0;

	if (n == 1)
	{
		while (b - a > 2 * e)
		{
			if (f1(a) * f1_2(a) > 0)
			{
				d = a - f1(a) / f1_1(a);
				c = (a * f1(b) - b * f1(a)) / (f1(b)-f1(a));
				a = d;
				b = c;
			}
			else
			{
				if (f1(b) * f1_2(b) > 0)
				{
					d = b - f1(b) / f1_1(b);
					c = (a * f1(b) - b * f1(a)) / (f1(b) - f1(a));
					b = d;
					a = c;
				}
			}
			it++;
		}
		return x = (a + b) / 2;
	}
	else
		if (n == 2)
		{
			while (b - a > 2 * e)
			{
				if (f2(a) * f2_2(a) > 0)
				{
					d = a - f2(a) / f2_1(a);
					c = (a * f2(b) - b * f2(a)) / (f2(b) - f2(a));
					a = d;
					b = c;
				}
				else
				{
					if (f2(b) * f2_2(b) > 0)
					{
						d = b - f2(b) / f2_1(b);
						c = (a * f2(b) - b * f2(a)) / (f2(b) - f2(a));
						b = d;
						a = c;
					}
				}
				it++;
			}
			return x = (a + b) / 2;
		}
		else return 0;
}