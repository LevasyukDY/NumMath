#pragma once
#include<iostream>
#include <vector>
#include <math.h>
#include <ctime>

typedef std::vector<std::vector<double>> matrix;

class Matrix
{
	private:
		matrix Matr;
	public:
		//Конструкторы класса
		Matrix();
		~Matrix();
		Matrix(unsigned Row, unsigned Col);

		enum ERRORS
		{
			IndexOutsideMatrix = 1, //Индекс вне границ матрицы
			MatricesNotEqual = 2, //Порядки матриц не равны
			LineNotEqualColoumn = 3, //Строка матрицы не равна стобцу другой матрицы
			DivByZero = 4, //Деление на ноль
			OffLineIndex = 5, //Индекс для доступа к строке, вне границ строк матрицы
			NotRectMatrix = 6, //Матрица не прямоугольная
			NotSquareMatric = 7, //Матрица не квадратная
			DeterminateIsZero = 8, //Определитель равен нулю
			OddElementsMatrix = 9 //Матрица с нечетным количеством эл.
		};

		//Задать и получить матрицу
		matrix GetMatrix();
		void SetMatrix(matrix Matr1);

		//Получить или установить эл. матрицы
		double GetElement(unsigned n, unsigned m);
		void SetElement(unsigned n, unsigned m, double Value);

		//Присвоит полученое значение новой матрице
		Matrix operator + (const Matrix& Matr2) const;
		Matrix operator * (const Matrix& Matr2) const;

		//Текущая матрица преобразуется в обратную
		void Inverse();

		//Вернет определитель матрицы, если та - квадратная
		double Detr() const;

	private:
		//Определитель матрицы 2 на 2
		double Detr(const matrix& M) const;
		//Нахождение определителей миноров матрицы
		double Detr(const matrix& M, unsigned Row, unsigned Col) const;

		//Проверка на не выход индекса за границы матрицы
		bool WithinBorders(unsigned IndexRow, unsigned IndexCol) const;
		//Проверка на равенстнво матриц
		bool EqualMatrix(const matrix& Matr1, const matrix& Matr2) const;
		//Проверка на равенство строки столбцу
		bool EqualRowCol(const matrix& Matr1, const matrix& Matr2) const;
		//Проверка на не ступенчатость матрицы
		bool RectMatrix(const matrix& Matr1) const;
		//Проверка матрицы на квадратность
		bool SquareMatrix(const matrix& Matr1) const;
		//Проверка на повторное использование строки, для нахождения обратной матрицы
		bool RepeatUsedLine(const std::vector<double>& ArrayIndexLine, unsigned IndexLine);
		std::vector<double> LineDivNumber(const std::vector<double>& Line, double Number);
		//Вычитание строк, одна из которых домножена на Index эл. первой
		std::vector<double> SubLine(const std::vector<double>& Line1, const std::vector<double>& Line2, unsigned Index);
		//Выравнивание еденичной матрицы, т.к. еденицы могут находится не на главной диагонали
		void Unit(matrix& Matr1);
};

