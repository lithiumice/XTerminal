#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_NUM 20
#define COUNT   (MAX_NUM / 2)

// 生成m个小于n的不重复随机数的算法
static void init_rand(int ayyr[], int max_count, int count)
{
	int w, t;

	srand((unsigned)time(NULL));
	//srand(seed);
	for (int i = 0; i < max_count; i++)
	    ayyr[i] = (i % count) + 1;
	for (int i = 0; i < max_count; i++)
	{
	    w = rand() % (count - (i % count)) + (i % count);
	    t = ayyr[i];
	    ayyr[i] = ayyr[w];
	    ayyr[w] = t;
	}
}

#if 0
void main()
{
	int a1[MAX_NUM] = {0};

	init_rand(a1, MAX_NUM, COUNT);

	for (int i = 0; i < MAX_NUM; i++)
	{
		if (i == 10)	printf("\n");
	    printf("%d ", a1[i]);
	}
	printf("\n");
}
#endif