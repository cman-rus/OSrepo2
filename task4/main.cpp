#include<stdio.h>
#include "main.h"


volatile int a[(1<<size) * (1<<size)];
volatile int b[(1<<size) * (1<<size)];
volatile int c[(1<<size) * (1<<size)];

int R()
{
	for (int x = 0; x < 1<<size; ++x)
	{
		for (int y = 0; y < 1<<size; ++y)
		{
			for (int i = 0; i < 1<<size; ++i)
			{
				c[x*(1<<size) + y] += a[x*(1<<size) + i] * b[i*(1<<size) + y];
			}
		}
	}

	return 0;

}

int Tmy()
{

	int tileSize = (1<<sT) * (1<<sT);

        int tmp = (1<<sT) * (1<<size);

	// алгоритм, не смотря на замечания, правильный. поясню его
	
	// cou - это количество сколько отрезков длины стороны матрицы T покроют сторону нашей матрицы
	// формула для общего случая, если стороны не кратные. в нашем случае - всегда cou = (1<<size)/(1<<sT). Я не рассматриваю общий случай - темболее сам алгоритм построен для того, чтоб все кратно было. просто захотелось такую формулу =)
	// для 1x1 получается 1<<size - что правильно
	// каой смысл от cou? мы разбиваем нашу матрицу c[1<<size][1<<size] на квадратики со сторонами 1<<sT. и первые два вложенных цикла бегут по этим квадратам
	int cou = ((1<<size)-1)/(1<<sT) + 1;
	
	for (int x = 0; x < cou; ++x)
        {
                for (int y = 0; y < cou; ++y)
                {
			// следующие 2 вложенных цикла пробегают по всем элементам квадратика размерами T из матрицы c[1<<size][1<<size]
			for(int i=0; i< 1<<sT; ++i)
			{
				for(int j=0; j< 1<<sT; ++j)
                       		{
					int x1 = x * (1<<sT) + i;
					int y1 = y * (1<<sT) + j;
						
					int posi = (x1 / (1<<sT)) * tmp + (1<<sT) * (x1 % (1<<sT));
					int posj = (y1 / (1<<sT)) * tileSize + y1 % (1<<sT);
					int pos = posi + posj;
					
					for (int k = 0; k < 1<<size; ++k)
                        		{
                		                c[pos] += a[posi + (k / (1<<sT)) * tileSize + k % (1<<sT)] * b[(k / (1<<sT)) * tmp + (1<<sT) * (k % (1<<sT)) + posj];
		                        }


                        	} 
			}
                }
        }

	// как-то так. извините, за корявый русский - лично могу подробней объяснить алгоритм и его корректность
	// просто мне показалось, что чем реже мы будем сдвигать окна тем лучше будет. именно для этого такое странное разбиение.


	return 0;
}

int T()
{
	int tileSize = (1<<sT) * (1<<sT);

	int tmp = (1<<sT) * (1<<size);
	
        for (int i = 0; i < 1<<size; ++i)
        {
		int posi = (i / (1<<sT)) * tmp + (1<<sT) * (i % (1<<sT));
                for (int j = 0; j < 1<<size; ++j)
                {
			int posj = (j / (1<<sT)) * tileSize + j % (1<<sT);
			int pos = posi + posj;

                        for (int k = 0; k < 1<<size; ++k)
                        {
				c[pos] += a[posi + (k / (1<<sT)) * tileSize + k % (1<<sT)] * b[(k / (1<<sT)) * tmp + (1<<sT) * (k % (1<<sT)) + posj];
                        }
                }
        }

	return 0;
}

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
//		printf("R\n");
		R();
	}
	else
	{
		if(argc == 2)
		{
//			printf("T\n");
			T();
		}
		else
		{
//                        printf("Tmy\n");
                        Tmy();
		}
	}
	return 0;
}
