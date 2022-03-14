#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_NUM 10
#define COUNT   10

// 生成m个小于n的不重复随机数的算法
static void init_rand(int ayyr[], int count, unsigned seed)
{
	int w, t;

	//srand((unsigned)time(seed));
	srand(seed);
	for (int i = 0; i < count; i++)
	    ayyr[i] = i + 1;
	for (int i = 0; i < count; i++)
	{
	    w = rand() % (count - i) + i;
	    t = ayyr[i];
	    ayyr[i] = ayyr[w];
	    ayyr[w] = t;
	}
}


#if 0
void main()
{
	int a1[COUNT] = {0};
	int a2[COUNT] = {0};

	init_rand(a1, COUNT, 50);
	init_rand(a2, COUNT, 100);

	for (int i = 0; i < COUNT; i++)
	    printf("%d ", a1[i]);
	printf("\n");
	for (int i = 0; i < COUNT; i++)
	    printf("%d ", a2[i]);
	printf("\n");
}

#endif
