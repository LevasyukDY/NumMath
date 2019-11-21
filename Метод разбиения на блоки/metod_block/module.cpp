#include "module.h"
#include <iostream>

using namespace std;

//нахождение обратной матрицы 2x2
vector_float reverse(vector_float A) 
{
	// запоминаем первый элемент
	float first_el = A[0][0];
	// находим определитель
	float det = A[0][0] * A[1][1] - A[1][0] * A[0][1];
	if (det == 0)
	{
		cout << "Определитель подматрицы равен 0." << endl;
		cout << "Система имеет бесконечное множество решений." << endl << endl;
		system("pause");
		exit(0);
	}

	A[0][0] = A[1][1]; 
	A[0][1] = -A[0][1]; // меняем значения
	A[1][0] = -A[1][0]; // элементов
	A[1][1] = first_el; 

	// находим элементы для обратной матрицы
	for (unsigned i = 0; i < 2; i++) 
	{
		for (unsigned j = 0; j < 2; j++) 
		{
			A[i][j] *= (1 / det);
		}
	}
	return A;
}

// Функция нахождения X и V
vector_float formula_XV(vector_float M, vector_float N, vector_float Q1, vector_float P) {

	vector_float C;
	C = memoVector(C, N.size(), N[0].size());
	C = mul(C, N, Q1);
	C = mul(C, C, P);

	for (unsigned i = 0; i < N.size(); i++)
		for (unsigned j = 0; j < N[i].size(); j++)
			C[i][j] = M[i][j] - C[i][j];

	C = reverse(C);

	return C;
}

// Умножение матрицы 2x2
vector_float mul(vector_float C, vector_float N, vector_float Q1) {
	float S;
	for (unsigned i = 0; i < N.size(); i++)
		for (unsigned j = 0; j < N[i].size(); j++) {
			S = 0;
			for (unsigned k = 0; k < N[i].size(); k++)
				S += N[i][k] * Q1[k][j];
			C[i][j] = S;
		}
	return C;
}

vector_float formula_UY(vector_float V, vector_float P, vector_float M1) {

	vector_float C;
	C = memoVector(C, V.size(), V[0].size());
	C = mul(C, V, P);
	C = mul(C, C, M1);

	for (unsigned i = 0; i < C.size(); i++)
		for (unsigned j = 0; j < C[i].size(); j++)
			C[i][j] *= -1;

	return C;
}

vector_float memoVector(vector_float A, unsigned n, unsigned m) {
	A.resize(n);
	for (unsigned i = 0; i < A.size(); i++) {
		A[i].resize(m);
	}
	return A;
}

// Вывод на экран матрицы
void printVector(vector_float A) 
{	
	for (unsigned i = 0; i < A.size(); i++)
	{
		for (unsigned j = 0; j < A[i].size(); j++)
		{
			if (A[i][j] >= 0 && A[i][j] < 10)
				cout << "  ";

			if (A[i][j] >= 10 || A[i][j] < 0)
				cout << " ";

			cout << round(A[i][j]);
			/*if (j < A[i].size() - 1)
				cout << "  ";*/
		}
		cout << endl;
	}
	cout << endl;
}

// Вывод на экран матрицы 4х4, имея 4 матрицы 2х2
void printMatrix(vector_float X, vector_float Y, vector_float U, vector_float V)
{
	for (unsigned i = 0; i < 2; i++)
	{
		for (unsigned j = 0; j < 2; j++)
		{
			if (X[i][j] >= 0 && X[i][j] < 10)
				cout << "  ";

			if (X[i][j] >= 10 || X[i][j] < 0)
				cout << " ";
			cout << round(X[i][j]);
		}
		for (unsigned j = 0; j < 2; j++)
		{
			if (Y[i][j] >= 0 && Y[i][j] < 10)
				cout << "  ";

			if (Y[i][j] >= 10 || Y[i][j] < 0)
				cout << " ";
			cout << round(Y[i][j]);
		}
		cout << endl;
	}
	for (unsigned i = 0; i < 2; i++)
	{
		for (unsigned j = 0; j < 2; j++)
		{
			if (U[i][j] >= 0 && U[i][j] < 10)
				cout << "  ";

			if (U[i][j] >= 10 || U[i][j] < 0)
				cout << " ";
			cout << round(U[i][j]);
		}
		for (unsigned j = 0; j < 2; j++)
		{
			if (V[i][j] >= 0 && V[i][j] < 10)
				cout << "  ";

			if (V[i][j] >= 10 || V[i][j] < 0)
				cout << " ";
			cout << round(V[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}