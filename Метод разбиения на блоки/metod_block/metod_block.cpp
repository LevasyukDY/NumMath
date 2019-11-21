#include <iostream>
#include <iomanip>
#include "module.h"

using namespace std;

int main() 
{
	setlocale(0, "");

	vector_float A = {{-1, -1, -1, -2},
					  { 2,  3,  4,  3},
					  {-2,  0,  1, -6},
					  {-2, -2, -3, -3}},
				 Q1, M1;					// Q1 и M1 - обратные матрицы Q и M

	vector_float M = {{ -1, -1 },
					  {  2,  3 }};

	vector_float N = {{ -1, -2 },
					  {  4,  3 }};

	vector_float P = {{ -2,  0 },
					  { -2, -2 }};

	vector_float Q = {{  1, -6 },
					  { -3, -3 }};

	cout << "Matrix A:" << endl;
	printVector(A);

	Q1 = reverse(Q); // шаг первый
	M1 = reverse(M); // шаг второй

	// шаг третий
	// получение матрицы X по формуле X = (M - NQ^-1*P)^-1
	vector_float X = formula_XV(M, N, Q1, P);

	// шаг четвертый
	// получение матрицы V по формуле V = (Q - PM^-1*N)^-1
	vector_float V = formula_XV(Q, P, M1, N);

	// шаг пятый
	// получение матрицы U по формуле U = -VPM^-1
	vector_float U = formula_UY(V, P, M1);

	// шаг шестой
	// получение матрицы Y по формуле U = -VPM^-1
	vector_float Y = formula_UY(X, N, Q1);

	cout << "Matrix A^-1:" << endl;
	printMatrix(X, Y, U, V);

	cout << "Matrix X:" << endl;
	printVector(X);
	cout << "Matrix Y:" << endl;
	printVector(Y);
	cout << "Matrix U:" << endl;
	printVector(U);
	cout << "Matrix V:" << endl;
	printVector(V);

	cout << endl;
	system("pause");
	return 0;
}