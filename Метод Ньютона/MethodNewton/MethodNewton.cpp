#include "Matrix.h"

using namespace std;

// Вариант 7
// f(x,y) = 1.5x^4 - 2.4x^3 + 1.44x^2 - 0.384x + 1.4y^2 - 1.4y + 0.3884

// Вектор анти-градиента
void W(float& x, float& y)
{
	// (x) Вектор градиента: 6x^3 - 7.2x^2 + 2.88x - 0.384
	// (x) Вектор анти-градиента: - 6x^3 + 7.2x^2 - 2.88x + 0.384
	// (x) Производная вектора градиента: 18x^2 - 14.4x + 2.88
	x = -6 * pow(x, 3) + 7.2 * pow(x, 2) - 2.88 * x + 0.384; 

	// (y) Вектор градиента: 2.8y - 1.4
	// (y) Вектор анти-градиента: - 2.8y + 1.4
	// (y) Производная вектора градиента: 2.8
	y = -2.8 * y + 1.4; 
}

// Матрица Гессе
float H_X(Matrix X)
{
	return 18 * pow(X.GetElement(0, 0), 2) - 14.4 * X.GetElement(0, 0) + 2.88;
}

int main()
{
	setlocale(0, "");

	Matrix X(2, 1), W_X(2, 1), X2;
	float x = 1, y = 1, x_new = 1, y_new = 1;

	X.SetElement(0, 0, x);
	X.SetElement(1, 0, y);

	Matrix H(2, 2);
	H.SetMatrix(matrix{ { 6.48, 0 } ,{ 0, 2.8 } });
	H.Inverse();

	W(x, y);
	W_X.SetElement(0, 0, x);
	W_X.SetElement(1, 0, y);

	X2 = X + (H * W_X);

	// Ввели дополнительные переменные, благодаря которым
	// будем проверять условие |W(X_k)| < E
	x_new = X2.GetElement(0, 0);
	y_new = X2.GetElement(1, 0);
	W(x_new, y_new);

	while (sqrt(x_new * x_new + y_new * y_new) > 0.0001f)
	{
		X.SetElement(0, 0, X2.GetElement(0, 0));
		X.SetElement(1, 0, X2.GetElement(1, 0));
		H.SetElement(0, 0, H_X(X));
		H.Inverse();

		x = X.GetElement(0, 0);
		y = X.GetElement(1, 0);
		W(x, y);
		W_X.SetElement(0, 0, x);
		W_X.SetElement(1, 0, y);

		X2 = X + (H * W_X);

		x_new = X2.GetElement(0, 0);
		y_new = X2.GetElement(1, 0);
		W(x_new, y_new);
	}

	cout << endl;
	cout << "[ " << X2.GetElement(0, 0) << " ; " << X2.GetElement(1, 0) << " ]" << endl << endl;

	system("pause");
	return 0;
}