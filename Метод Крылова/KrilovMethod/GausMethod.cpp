#include <iostream>
#include <vector>

void Gaus(unsigned n, std::vector<std::vector<double>> a, float b[]) 
{
	unsigned i, j, id_row, id_row_old = 1;
	int k, g = 0;
	float lead;

	// Поиск ненулевого элемента в столбце
	for (j = 0; j < n; j++) 
		for (i = g; i < n; i++) 
			if (a[i][j] != 0)
			{
				id_row = i; // Запоминаем номер строки
				unsigned flag;

				if (id_row_old != id_row)
					flag = 0;
				else
					flag = 1;

				if (flag == 0) // Если текущая строка не была использована
				{
					id_row_old = id_row;
					lead = a[i][j]; // Выбираем первый входящий в нее элемент
					for (k = j; k < n; k++)
						a[i][k] /= lead; // Делим всю строку на него
					b[i] /= lead;

					g = i;
					// Вычитание строк
					for (k = 0; k < n; k++)
						for (int w = 0; w < n; w++) 
						{
							float buf = a[k][w]; // Сохраняем элемент строки, который будет множителем 
							if ((w == j) && (k != g)) 
							{
								int p = k; int c = w;
								a[p][c] = buf; // Сохраняем строку

								for (c = w; c < n; c++) 
									a[p][c] -= buf * a[g][c];

								b[k] -= buf * b[i];
							}
						}
					i = n; // Для перехода к след. столбцу
				}
			}
}