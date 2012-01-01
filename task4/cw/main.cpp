#include<stdio.h>
volatile int a[1024*16][1024*16];
int main()
{
	//volatile int a[1024*4][1024*4];
	volatile int c;
	for(int i=0; i<1024*16; ++i)
		for(int j=0; j<1024*16;++j)
			c += a[i][j];

	printf("%d\n", c);
	return 0;
}
