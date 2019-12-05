#include "module.h"

// функция под буквой а
double f1(double x) 
{
	return 7 * x + pow(5, x) - 2; 
}


// функция под буквой б
double f2(double x) 
{
	return -1 * pow(x, 3) - 3 * pow(x, 2) - 5 * x + 4;
}


// вычисления
double calc(double a, double b, unsigned n, unsigned &it)
{
	double e = 0.0001, x = 0, c = 0;

	if (n == 1)
	{
		while (b - a > 2 * e)
		{
			c = (a + b) / 2;
			if (f1(a) * f1(c) < 0)
				b = c;
			else
				if (f1(b) * f1(c) < 0)
					a = c;
			it++;
		}
		return x = (a + b) / 2;
	}
	else
		if (n == 2)
		{
			while (b - a > 2 * e)
			{
				c = (a + b) / 2;
				if (f2(a) * f2(c) < 0)
					b = c;
				else
					if (f2(b) * f2(c) < 0)
						a = c;
				it++;
			}
			return x = (a + b) / 2;
		}
		else return 0;
}