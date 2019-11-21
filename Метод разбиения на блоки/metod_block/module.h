#pragma once
#include <vector>

using vector_float = std::vector<std::vector<float>>;

//нахождение обратной матрицы 2x2
vector_float reverse(vector_float A);

// Функция нахождения матриц X и V
vector_float formula_XV(vector_float M, vector_float N, vector_float Q1, vector_float P);

// Умножение матрицы 2x2
vector_float mul(vector_float C, vector_float N, vector_float Q1);

// Функция нахождения матриц U и Y
vector_float formula_UY(vector_float V, vector_float P, vector_float M1);

// Функция выделения памяти под массив
vector_float memoVector(vector_float A, unsigned n, unsigned m);

// Вывод на экран матрицы 2х2
void printVector(vector_float A);

// Вывод на экран матрицы 4х4, имея 4 матрицы 2х2
void printMatrix(vector_float X, vector_float Y, vector_float U, vector_float V);