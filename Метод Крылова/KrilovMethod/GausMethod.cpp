#include <iostream>
#include <vector>

void Gaus(unsigned n, std::vector<std::vector<double>> a, float b[]) 
{
	unsigned i, j, id_row, id_row_old = 1;
	int k, g = 0;
	float lead;

	// ����� ���������� �������� � �������
	for (j = 0; j < n; j++) 
		for (i = g; i < n; i++) 
			if (a[i][j] != 0)
			{
				id_row = i; // ���������� ����� ������
				unsigned flag;

				if (id_row_old != id_row)
					flag = 0;
				else
					flag = 1;

				if (flag == 0) // ���� ������� ������ �� ���� ������������
				{
					id_row_old = id_row;
					lead = a[i][j]; // �������� ������ �������� � ��� �������
					for (k = j; k < n; k++)
						a[i][k] /= lead; // ����� ��� ������ �� ����
					b[i] /= lead;

					g = i;
					// ��������� �����
					for (k = 0; k < n; k++)
						for (int w = 0; w < n; w++) 
						{
							float buf = a[k][w]; // ��������� ������� ������, ������� ����� ���������� 
							if ((w == j) && (k != g)) 
							{
								int p = k; int c = w;
								a[p][c] = buf; // ��������� ������

								for (c = w; c < n; c++) 
									a[p][c] -= buf * a[g][c];

								b[k] -= buf * b[i];
							}
						}
					i = n; // ��� �������� � ����. �������
				}
			}
}