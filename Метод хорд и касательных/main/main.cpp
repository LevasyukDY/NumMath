#include <iostream>
#include "module.h"

using namespace std;

int main()
{
	setlocale(0, "");

	double a = 0, b = 1, // отрезок неопределённости
		 x = 0;
	unsigned n = 1, it = 0;

	x = calc(a, b, n, it);
	cout << "(а) x = " << x << "\ni = " << it << "\n";

	n = 2;
	x = calc(a, b, n, it);
	cout << "(б) x = " << x << "\ni = " << it << "\n";


	system("pause");
	return 0;
}
