#include "Matrix.h"

//������������ ������
Matrix::Matrix()
{
}
Matrix::~Matrix()
{
}
Matrix::Matrix(unsigned Row, unsigned Col)
{
	Matr.resize(Row);
	for (unsigned i = 0; i < Row; i++)
		Matr[i].resize(Col);
}

//������ � �������� �������
matrix Matrix::GetMatrix()
{
	return Matr;
}

void Matrix::SetMatrix(matrix Matr1)
{
	Matr = Matr1;
}

//�������� ��� ���������� ��. �������
double Matrix::GetElement(unsigned n, unsigned m)
{
	if (WithinBorders(n, m))
		return Matr[n][m];
	else
		throw IndexOutsideMatrix;
}

void Matrix::SetElement(unsigned n, unsigned m, double Value)
{
	if (WithinBorders(n, m))
		Matr[n][m] = Value;
	else
		throw IndexOutsideMatrix;
}

//�������� ��������� �������� ����� �������
Matrix Matrix::operator + (const Matrix& Matr2) const
{
	if (!EqualMatrix(Matr, Matr2.Matr)) throw MatricesNotEqual;

	Matrix Matr3;
	Matr3.Matr = Matr;

	for (unsigned i = 0; i < Matr.size(); i++)
		for (unsigned j = 0; j < Matr[i].size(); j++)
			Matr3.Matr[i][j] = Matr[i][j] + Matr2.Matr[i][j];

	return Matr3;
}

Matrix Matrix::operator * (const Matrix& Matr2) const
{
	if (!EqualRowCol(Matr, Matr2.Matr)) throw LineNotEqualColoumn;

	Matrix Matr3 = Matrix(Matr.size(), Matr2.Matr[0].size());

	for (unsigned i = 0; i < Matr.size(); i++)
		for (unsigned j = 0; j < Matr2.Matr[0].size(); j++)
			for (unsigned k = 0; k < Matr2.Matr.size(); k++)
				Matr3.Matr[i][j] += Matr[i][k] * Matr2.Matr[k][j];

	return Matr3;
}

//�������� �� �� ����� �� ������� �������
bool Matrix::WithinBorders(unsigned IndexRow, unsigned IndexCol) const
{
	return (((IndexRow >= 0 && IndexRow < Matr.size()))
		&& (IndexCol >= 0 && IndexCol < Matr[IndexRow].size()))
		? true
		: false;
}

//������� ������� ������������� � ��������
void Matrix::Inverse()
{
	if (!SquareMatrix(Matr)) throw NotSquareMatric;
	if (Detr() == 0) throw DeterminateIsZero;

	matrix MatrE;//������� ������� � ��������� �������
	std::vector<double> NumUsedLine;//������ � �������� ���. �����
	MatrE.resize(Matr.size());
	NumUsedLine.resize(Matr.size());
	for (unsigned i = 0; i < MatrE.size(); i++)
	{
		MatrE[i].resize(MatrE.size() * 2);
		NumUsedLine[i] = -1;
	}
	//������������� ������� � ���������
	for (unsigned i = 0; i < MatrE.size(); i++)
		for (unsigned j = 0; j < MatrE[i].size(); j++)
		{
			if (j < Matr.size())
				MatrE[i][j] = Matr[i][j];
			else
				MatrE[i][j] = ((j - Matr.size()) == i) ? 1 : 0;
		}

	//�������������� ��������� ������� � ���������
	//��� ��������� ��������
	for (unsigned j = 0; j < Matr.size(); j++)
		for (unsigned i = 0; i < Matr.size(); i++)
			if (MatrE[i][j] != 0 && RepeatUsedLine(NumUsedLine, i))
			{
				NumUsedLine[j] = i;//������� ����� ���������� ��.
				MatrE[i] = LineDivNumber(MatrE[i], MatrE[i][j]);//������� �� ���� ������

				for (unsigned k = 0; k < MatrE.size(); k++)
				{
					if (k == i) continue;
					MatrE[k] = SubLine(MatrE[k], MatrE[i], j);//������ ������ �� ���������
				}

				break;
			}

	Unit(MatrE); //���� ������� ����������� � ������������ �������

	for (unsigned i = 0; i < Matr.size(); i++)
		for (unsigned j = 0; j < Matr.size(); j++)
			Matr[i][j] = MatrE[i][j + Matr.size()];
}

//�������� �� ��������� ������������� ������, ��� ���������� �������� �������
bool Matrix::RepeatUsedLine(const std::vector<double>& ArrayIndexLine, unsigned IndexLine)
{
	for (unsigned i = 0; i < ArrayIndexLine.size(); i++)
		if (IndexLine == ArrayIndexLine[i]) return false;

	return true;
}

//������� ������ ������� �� �����
std::vector<double> Matrix::LineDivNumber(const std::vector<double>& Line, double Number)
{
	std::vector<double> Result;
	Result.resize(Line.size());
	for (unsigned i = 0; i < Line.size(); i++)
	{
		Result[i] = Line[i] / Number;
	}
	return Result;
}
//��������� �����, ���� �� ������� ��������� �� Index ��. ������
std::vector<double> Matrix::SubLine(const std::vector<double>& Line1, const std::vector<double>& Line2, unsigned Index)
{
	std::vector<double> Result;
	Result.resize(Line1.size());
	for (unsigned i = 0; i < Line1.size(); i++)
	{
		Result[i] = Line1[i] - (Line2[i] * Line1[Index]);
	}
	return Result;
}
//������������ ��������� �������
void Matrix::Unit(matrix& Matr1)
{
	std::vector<double> CopyLine;
	for (unsigned j = 0; j < Matr1.size(); j++)
		for (unsigned i = 0; i < Matr1.size(); i++)
			if (Matr1[i][j] == 1)
			{
				CopyLine = Matr1[j];
				Matr1[j] = Matr1[i];
				Matr1[i] = CopyLine;
				break;
			}

}

//������ ������������ �������, ���� �� - ����������
double Matrix::Detr() const
{
	if (!SquareMatrix(Matr)) throw NotSquareMatric;

	if (Matr.size() == 1) return Matr[0][0];
	if (Matr.size() == 2) return Detr(Matr);

	double Determinate = 0;
	for (unsigned i = 0; i < Matr[0].size(); i++)
		Determinate += Detr(Matr, 0, i);

	return Determinate;
}

//������������ ������� 2 �� 2
double Matrix::Detr(const matrix& M) const
{
	//std::cout << M[0][0] * M[1][1] - M[0][1] * M[1][0];
	return (M[0][0] * M[1][1]) - (M[0][1] * M[1][0]);

}

//���������� ������������� ������� �������
double Matrix::Detr(const matrix& M, unsigned Row, unsigned Col) const
{
	matrix Minor;
	Minor.resize(M.size() - 1);
	for (unsigned i = 0; i < Minor.size(); i++)
		Minor[i].resize(M[i].size() - 1);

	//������������� ������� � �������
	unsigned i1 = 0, j1 = 0;
	for (unsigned i = 0; i < M.size(); i++)
	{
		if (i == Row) continue;
		for (unsigned j = 0; j < M[i].size(); j++)
		{
			if (j == Col) continue;
			Minor[i1][j1] = M[i][j];
			j1++;
		}
		i1++;
		j1 = 0;
	}

	//������ ������������ ������ 2�2
	if (Minor.size() == 2) return (pow(-1, Row + Col) * M[Row][Col]) * Detr(Minor);

	//����� �������� ���������� ������ ��� �� ��������
	double Determinate = 0;
	for (unsigned i = 0; i < Minor[0].size(); i++)
		Determinate += (pow(-1, Row + Col) * M[Row][Col]) * Detr(Minor, 0, i);
	return Determinate;
}

//�������� �� ���������� ������
bool Matrix::EqualMatrix(const matrix& Matr1, const matrix& Matr2) const
{
	if (Matr1.size() != Matr2.size()) return false;

	//����������� �� ������ ���-�� �����,
	//�� � ���-�� ��. � ������, �.�. ������� ����� ���� �����������
	for (unsigned i = 0; i < Matr1.size(); i++)
		if (Matr1[i].size() != Matr2[i].size()) return false;

	return true;
}

//�������� �� ��������� ������ �������
bool Matrix::EqualRowCol(const matrix& Matr1, const matrix& Matr2) const
{
	//������� �� ������ ���� �����������
	if (!RectMatrix(Matr1) || !RectMatrix(Matr2)) return false;

	if (Matr1[0].size() != Matr2.size()) return false;

	return true;
}

//�������� �� �� ������������� �������
bool Matrix::RectMatrix(const matrix& Matr1) const
{
	for (unsigned i = 0; i < Matr1.size(); i++)
		if (Matr1[i].size() != Matr1[0].size()) return false;
	return true;
}

//�������� ������� �� ������������
bool Matrix::SquareMatrix(const matrix& Matr1) const
{
	if (!RectMatrix(Matr1)) return false; //��� ������ ������� �� ������ ���� ����������
	if (Matr1.size() != Matr1[0].size()) return false;
	return true;
}